/*
 * This file belongs to Brown University's computer
 * science department as part of csci1951L - Blockchains
 * and cryptocurrencies.
 *
 * This software was developed by Colby Anderson (HTA)
 * and Parker Ljung (TA) of csci1951L in Summer of 2021.
 */

#include <coin_database.h>
#include <rathcrypto.h>
#include <iostream>

CoinLocator::CoinLocator(
        uint32_t transaction_hash_, uint8_t output_index_)
        : transaction_hash(transaction_hash_),
          output_index(output_index_) {}

std::string CoinLocator::serialize(const CoinLocator& coin_locator) {
    return std::to_string(coin_locator.transaction_hash) + "-" +
           std::to_string(coin_locator.output_index);
}

std::unique_ptr<CoinLocator> CoinLocator::deserialize(const std::string& serialized_coin_locator) {
    std::string transaction_hash = serialized_coin_locator.substr(0, serialized_coin_locator.find("-"));
    std::string output_index = serialized_coin_locator.substr(serialized_coin_locator.find("-") + 1, serialized_coin_locator.size());
    return std::make_unique<CoinLocator>(std::stoul (transaction_hash,nullptr,0), std::stoul (output_index,nullptr,0));
}

std::string CoinLocator::serialize_from_construct(uint32_t transaction_hash, uint8_t output_index) {
    return std::to_string(transaction_hash) + "-" +
           std::to_string(output_index);
}

CoinDatabase::CoinDatabase() : _mempool_capacity(50), _main_cache_capacity(50) {
    _database = std::make_unique<Database>();
}

bool CoinDatabase::validate_block(const std::vector<std::unique_ptr<Transaction>>& transactions)
{
    for(const auto& transaction : transactions)
    {
        if(!validate_transaction(*transaction.get()))
            return false;
    }
    return true;
}

//Validate transaction should just check that the inputs of each transaction are actually referencing real UTXO.
// To check for this, you should query the main cache.
// Note, if the main cache does not have this information, you must query the database
// as well. These should probably be helper methods.
bool CoinDatabase::validate_transaction(const Transaction& transaction)
{
    std::vector<TransactionInput> inputs_not_in_cache;
    for (auto& input: transaction.transaction_inputs)
    {
        CoinLocator* coin_locator = new CoinLocator(input->reference_transaction_hash, input->utxo_index);
        if (!this->_main_cache.contains(CoinLocator::serialize(*coin_locator)))
        {
            inputs_not_in_cache.push_back(*input);
        }
    }
    for (auto& input : inputs_not_in_cache) {
        std::string hash = std::to_string(input.reference_transaction_hash);
        const auto &coin_record_serialized = this->_database->get_safely(hash);
        auto coin_record = CoinRecord::deserialize(coin_record_serialized);
        bool found = false;

        for (auto &utxo : coin_record->utxo) {
            if (utxo == input.utxo_index) {
                found = true;
                break;
            }
        }
        if(!found) {
            std::cout << "[CoinDatabase::validate_transaction] Transaction Invalid: UTXO not found for TX input referencing: " << hash <<
                " at index "<< std::to_string(input.utxo_index) << std::endl;
            return false;
        }
    }
    return true;
}

void CoinDatabase::remove_transactions_from_mempool(const std::vector<std::unique_ptr<Transaction>>& transactions)
{
    for(auto& transaction : transactions)
    {
        this->_mempool_cache.erase(RathCrypto::hash(Transaction::serialize(*transaction.get())));
    }
}

bool CoinDatabase::validate_and_store_block(std::vector<std::unique_ptr<Transaction>> transactions)
{
    bool valid_block = this->validate_block(transactions);
    if(valid_block)
    {
        this->store_block(std::move(transactions));
    }
    return false;
}
bool CoinDatabase::validate_and_store_transaction(std::unique_ptr<Transaction> transaction)
{
    bool valid_transaction = this->validate_transaction(*transaction);
    if(valid_transaction)
    {
        this->store_transaction(std::move(transaction));
    }
    return false;
}

void CoinDatabase::store_transaction(std::unique_ptr<Transaction> transaction)
{
    auto hash = RathCrypto::hash(Transaction::serialize(*transaction));
    std::cout << "[CoinDatabase::store_transaction] Storing to mempool: " <<  hash << std::endl;
    store_transaction_in_mempool(std::move(transaction));
}

void CoinDatabase::store_block(std::vector<std::unique_ptr<Transaction>> transactions) {
    remove_transactions_from_mempool(transactions);

    store_transactions_to_main_cache(std::move(transactions));
}

void CoinDatabase::store_transactions_to_main_cache(std::vector<std::unique_ptr<Transaction>> transactions) {

    for(auto& transaction : transactions){
        auto hash = RathCrypto::hash(Transaction::serialize(*transaction));
        int output_count = transaction->transaction_outputs.size();
        std::cout << "[CoinDatabase::store_transactions_to_main_cache] Storing to main cache: " <<  hash <<
        " with " << output_count << " outputs" <<std::endl;
        //Take all of the inputs and remove the spent UTXO
        for(auto& input : transaction->transaction_inputs){
            //Check main cache, mark as spend if found
            auto locator = new CoinLocator(input->reference_transaction_hash, input->utxo_index);
            auto serialized_locator = CoinLocator::serialize(*locator);
            if(_main_cache.contains(serialized_locator)){
                _main_cache[serialized_locator]->is_spent = true;
            }
            else{
                // Have to check the database
                // Get the record for a given transaction
                std::string transaction_hash = std::to_string(input->reference_transaction_hash);
                if(!(_database->contains(transaction_hash))){
                    continue;
                }
                auto db_result = _database->get_safely(transaction_hash);
                auto coin_record = CoinRecord::deserialize(db_result);
                auto it = std::find(coin_record->utxo.begin(),
                                    coin_record->utxo.end(),
                                    locator->output_index);
                int index = it - coin_record->utxo.begin(); //The current index in the vector
                coin_record->utxo.erase(coin_record->utxo.begin() + index);
                coin_record->amounts.erase(coin_record->amounts.begin() + index);
                coin_record->public_keys.erase(coin_record->public_keys.begin() + index);
                _database->put_safely(transaction_hash, CoinRecord::serialize(*coin_record));
            }
        }
        // Add all of the outputs to the main cache
        for(int i = 0; i < output_count; i++){
            auto& txo = transaction->transaction_outputs[i];
            auto locator = new CoinLocator(hash, i);
            std::cout << "[CoinDatabase::store_transaction_to_main_cache] Storing UTXO Tx: " << hash << " Idx: " << i << std::endl;
            auto record = std::make_unique<Coin>(std::move(txo), false);
            _main_cache[CoinLocator::serialize(*locator)] = std::move(record);
            _main_cache_size += 1;
            if(_main_cache_size >= _main_cache_capacity){
                flush_main_cache();
            }
        }
    }
}

void CoinDatabase::store_transaction_in_mempool(std::unique_ptr<Transaction> transaction) {
    if(_mempool_size < _mempool_capacity){
        auto hash = RathCrypto::hash(Transaction::serialize(*transaction));
        _mempool_cache[hash] = std::move(transaction);
    }
}

void CoinDatabase::flush_main_cache() {
    std::cout << "[CoinDatabase::flush_main_cache] Flushing cache " << std::endl;
    for(auto& entry : _main_cache){
        auto coin_locator = CoinLocator::deserialize(entry.first);
        std::string transaction_hash = std::to_string(coin_locator->transaction_hash);
        if(_database->contains(transaction_hash)){
            auto coin_record = CoinRecord::deserialize(_database->get_safely(transaction_hash));
            if(entry.second->is_spent){
                // Needs to be removed
                if(!(_database->contains(transaction_hash))){
                    continue;
                }
                auto db_result = _database->get_safely(transaction_hash);

                auto coin_record = CoinRecord::deserialize(db_result);
                auto it = std::find(coin_record->utxo.begin(),
                                    coin_record->utxo.end(),
                                    coin_locator->output_index);
                int index = it - coin_record->utxo.begin(); //The current index in the vector
                coin_record->utxo.erase(coin_record->utxo.begin() + index);
                coin_record->amounts.erase(coin_record->amounts.begin() + index);
                coin_record->public_keys.erase(coin_record->public_keys.begin() + index);
                _database->put_safely(transaction_hash, CoinRecord::serialize(*coin_record));
            }
            else{
                // Needs to be added
                coin_record->utxo.push_back(coin_locator->output_index);
                coin_record->amounts.push_back(entry.second->transaction_output->amount);
                coin_record->public_keys.push_back(entry.second->transaction_output->public_key);
                _database->put_safely(transaction_hash, CoinRecord::serialize(*coin_record));
            }
        }
        else{
            if(entry.second->is_spent){
                // Nothing needs to be done, no utxo left
            }
            else{
                // Needs to be added to the database
                std::vector<uint32_t> utxo = { coin_locator->output_index };
                std::vector<uint32_t> public_keys = { entry.second->transaction_output->public_key };
                std::vector<uint32_t> amounts = { entry.second->transaction_output->amount };
                auto record = new CoinRecord(0, utxo, amounts, public_keys);
                _database->put_safely(transaction_hash, CoinRecord::serialize(*record));
            }
        }
    }
    _main_cache.clear();
    _main_cache_size = 0;
}

std::unique_ptr<TransactionOutput> CoinDatabase::get_utxo(uint32_t transaction_hash, uint32_t output_index) {
    // First try the main cache
    auto locator = new CoinLocator(transaction_hash, output_index);
    auto serialized_locator = CoinLocator::serialize(*locator);
    if(_main_cache.contains(serialized_locator)){
        std::unique_ptr<Coin>& result = _main_cache[serialized_locator];
        return std::move(result->transaction_output);
    }
    else {
        //Search database
        auto string_hash = std::to_string(transaction_hash);
        if(!(_database->contains(string_hash))){
            return nullptr;
        }
        auto db_result = _database->get_safely(string_hash);
        auto coin_record = CoinRecord::deserialize(db_result);
        auto it = std::find(coin_record->utxo.begin(),
                    coin_record->utxo.end(),
                    output_index);
        int index = it - coin_record->utxo.begin(); //The current index in the vector
        auto txo = std::make_unique<TransactionOutput>(coin_record->amounts[index],
                                                       coin_record->public_keys[index]);
        return txo;
    }
}

void CoinDatabase::undo_coins(std::vector<std::unique_ptr<UndoBlock>> undo_blocks) {
    for(auto& undo_block : undo_blocks){
        int total_records = undo_block->transaction_hashes.size();
        for(int i = 0; i < total_records; i++){
            auto transaction_hash = undo_block->transaction_hashes[i];
            auto& undo_coin_record = undo_block->undo_coin_records[i];
            for(int j = 0; j < undo_coin_record->public_keys.size(); j++){
                auto utxo_index = undo_coin_record->utxo[j];
                auto locator = new CoinLocator(transaction_hash, utxo_index);
                std::cout << "[CoinDatabase::undo_coins] Removing UTXO at TX: " << transaction_hash
                    << " and index " << utxo_index << std::endl;
                auto key = CoinLocator::serialize(*locator);
                if(_main_cache.contains(key)){
                    _main_cache[key]->is_spent = false;
                }
                else {
                    // Check the database
                    if(!(_database->contains(std::to_string(transaction_hash)))){
                        continue;
                    }
                    auto db_result = _database->get_safely(std::to_string(transaction_hash));
                    auto coin_record = CoinRecord::deserialize(db_result);
                    auto it = std::find(coin_record->utxo.begin(),
                                        coin_record->utxo.end(),
                                        utxo_index);
                    int index = it - coin_record->utxo.begin();
                    coin_record->utxo.erase(coin_record->utxo.begin() + index);
                    coin_record->amounts.erase(coin_record->amounts.begin() + index);
                    coin_record->public_keys.erase(coin_record->public_keys.begin() + index);
                    _database->put_safely(std::to_string(transaction_hash), CoinRecord::serialize(*coin_record));
                }
            }
        }
    }
}
