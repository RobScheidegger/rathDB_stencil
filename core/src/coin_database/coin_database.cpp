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
    auto&& inputs = transaction.transaction_inputs;

    auto&& remaining_inputs = find_inputs_in_main_cache(inputs);

    auto&& not_in_either = find_inputs_in_database(remaining_inputs);

    return not_in_either.size() == 0;
}

// Returns all of the transaction inputs not in the main cache
std::vector<std::unique_ptr<TransactionInput>> CoinDatabase::find_inputs_in_main_cache(const std::vector<std::unique_ptr<TransactionInput>>& inputs)
{

    std::vector<std::unique_ptr<TransactionInput>> not_found_inputs;
    for (auto& input: inputs)
    {
        CoinLocator* coin_locator = new CoinLocator(input->reference_transaction_hash, input->utxo_index);
        if (!this->_main_cache.contains(CoinLocator::serialize(*coin_locator)))
        {
            //not_found_inputs.push_back(std::move(input));
        }
    }
    return not_found_inputs;
}

// Returns all of the transaction inputs not in the database
std::vector<std::unique_ptr<TransactionInput>> CoinDatabase::find_inputs_in_database(const std::vector<std::unique_ptr<TransactionInput>>& inputs)
{
    //Assemble a vector of all the transaction keys
    std::vector<std::string> keys;
    for (auto& input : inputs)
    {
        keys.push_back(std::to_string(input->reference_transaction_hash));
    }
    const auto& blocks = this->_database->batch_read_safely(keys);
    for(auto& block : blocks){

    }
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
        //this->store_block(transactions);
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

}