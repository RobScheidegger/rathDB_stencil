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
    auto inputs = &transaction.transaction_inputs;

    auto remaining_inputs = &find_inputs_in_main_cache(&inputs);


}

std::vector<std::unique_ptr<TransactionInput>> CoinDatabase::find_inputs_in_main_cache(std::vector<std::unique_ptr<TransactionInput>>& inputs)
{

}