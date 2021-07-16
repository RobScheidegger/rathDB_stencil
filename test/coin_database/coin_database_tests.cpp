/*
 * This file belongs to Brown University's computer
 * science department as part of csci1951L - Blockchains
 * and cryptocurrencies.
 *
 * This software was developed by Colby Anderson (HTA)
 * and Parker Ljung (TA) of csci1951L in Summer of 2021.
 */

#include <gtest/gtest.h>
#include <coin_record.h>
#include <coin_database.h>
#include <rathcrypto.h>

TEST(CoinLocator, Serialize) {
    CoinLocator coin_locator = CoinLocator(40, 33);
    std::string serialized_coin_locator = CoinLocator::serialize(coin_locator);
    std::unique_ptr<CoinLocator> deserialized_coin_locator = CoinLocator::deserialize(serialized_coin_locator);
    EXPECT_EQ(coin_locator.output_index, deserialized_coin_locator->output_index);
    EXPECT_EQ(deserialized_coin_locator->output_index, 33);

    std::string serialized_coin_locator2 = CoinLocator::serialize_from_construct(22, 19);
    std::unique_ptr<CoinLocator> deserialized_coin_locator2 = CoinLocator::deserialize(serialized_coin_locator2);
    EXPECT_EQ(deserialized_coin_locator2->output_index, 19);
}

TEST(CoinRecord, Serialize) {
    std::vector<uint32_t> utxo = {99};
    std::vector<uint32_t> amounts = {12};
    std::vector<uint32_t> public_keys = {14};
    CoinRecord coin_record = CoinRecord(99, std::move(utxo), std::move(amounts),
                                        std::move(public_keys));
    std::string serialized_coin_record = CoinRecord::serialize(coin_record);
    std::unique_ptr<CoinRecord> deserialized_coin_record = CoinRecord::deserialize(serialized_coin_record);
    EXPECT_EQ(coin_record.version, deserialized_coin_record->version);
    EXPECT_EQ(deserialized_coin_record->version, 99);
}

TEST(CoinDatabase, StoredAndValidatesBlockValid){
    auto db = std::make_unique<CoinDatabase>();
    std::vector<std::unique_ptr<TransactionInput>> inputs;
    inputs.push_back(std::move(std::make_unique<TransactionInput>(0, 1, 0)));

    std::vector<std::unique_ptr<TransactionOutput>> outputs;
    outputs.push_back(std::move(std::make_unique<TransactionOutput>(0,1)));

    auto transaction =std::make_unique<Transaction>(std::move(inputs),std::move(outputs));
    auto tx_hash = RathCrypto::hash(Transaction::serialize(*transaction));

    db->store_transaction(std::move(transaction));

    std::vector<std::unique_ptr<TransactionInput>> inputs_new;
    inputs_new.push_back(std::move(std::make_unique<TransactionInput>(tx_hash, 0, 11)));

    std::vector<std::unique_ptr<TransactionOutput>> outputs_new;
    outputs_new.push_back(std::move(std::make_unique<TransactionOutput>(0,1)));

    auto transaction_new = std::make_unique<Transaction>(std::move(inputs),std::move(outputs));

    ASSERT_TRUE(db->validate_transaction(*transaction_new));
}

TEST(CoinDatabase, RejectInvalidTransaction){
    auto db = std::make_unique<CoinDatabase>();
    std::vector<std::unique_ptr<TransactionInput>> inputs;
    inputs.push_back(std::move(std::make_unique<TransactionInput>(31823, 1, 0)));

    std::vector<std::unique_ptr<TransactionOutput>> outputs;
    outputs.push_back(std::move(std::make_unique<TransactionOutput>(0,1)));

    auto transaction =std::make_unique<Transaction>(std::move(inputs),std::move(outputs));
    ASSERT_FALSE(db->validate_transaction(*transaction));
}

TEST(CoinDatabase, RejectsInvalidBlock){
    auto db = std::make_unique<CoinDatabase>();
    std::vector<std::unique_ptr<TransactionInput>> inputs;
    inputs.push_back(std::move(std::make_unique<TransactionInput>(31823, 1, 0)));

    std::vector<std::unique_ptr<TransactionOutput>> outputs;
    outputs.push_back(std::move(std::make_unique<TransactionOutput>(0,1)));

    std::vector<std::unique_ptr<Transaction>> transactions;
    transactions.push_back(std::move(std::make_unique<Transaction>(std::move(inputs),std::move(outputs))));

    ASSERT_FALSE(db->validate_block(std::move(transactions)));
}

TEST(CoinDatabase, StoresAndValidatesValidBlock){
    auto db = std::make_unique<CoinDatabase>();
    std::vector<std::unique_ptr<TransactionInput>> inputs;
    inputs.push_back(std::move(std::make_unique<TransactionInput>(0, 1, 0)));

    std::vector<std::unique_ptr<TransactionOutput>> outputs;
    outputs.push_back(std::move(std::make_unique<TransactionOutput>(0,1)));

    auto transaction = std::make_unique<Transaction>(std::move(inputs),std::move(outputs), 190, 2);
    std::vector<std::unique_ptr<Transaction>> transactions;
    auto tx_hash = RathCrypto::hash(Transaction::serialize(*transaction));
    transactions.push_back(std::move(transaction));

    db->store_block(std::move(transactions));

    std::vector<std::unique_ptr<TransactionInput>> inputs_new;
    inputs_new.push_back(std::move(std::make_unique<TransactionInput>(tx_hash, 0, 11)));

    std::vector<std::unique_ptr<TransactionOutput>> outputs_new;
    outputs_new.push_back(std::move(std::make_unique<TransactionOutput>(0,1)));

    auto transaction_new = std::make_unique<Transaction>(std::move(inputs_new),std::move(outputs_new));
    std::vector<std::unique_ptr<Transaction>> transactions_new;
    transactions_new.push_back(std::move(transaction_new));

    ASSERT_TRUE(db->validate_block(std::move(transactions_new)));
}

TEST(CoinDatabase, FlushMainCacheRemovesEntries){
    auto db = std::make_unique<CoinDatabase>();
    std::vector<std::unique_ptr<TransactionInput>> inputs;
    inputs.push_back(std::move(std::make_unique<TransactionInput>(0, 1, 0)));

    std::vector<std::unique_ptr<TransactionOutput>> outputs;
    outputs.push_back(std::move(std::make_unique<TransactionOutput>(0,1)));

    auto transaction =std::make_unique<Transaction>(std::move(inputs),std::move(outputs));
    auto tx_hash = RathCrypto::hash(Transaction::serialize(*transaction));

    db->store_transaction(std::move(transaction));
    db->flush_main_cache();

    std::vector<std::unique_ptr<TransactionInput>> inputs_new;
    inputs_new.push_back(std::move(std::make_unique<TransactionInput>(tx_hash, 0, 11)));

    std::vector<std::unique_ptr<TransactionOutput>> outputs_new;
    outputs_new.push_back(std::move(std::make_unique<TransactionOutput>(0,1)));

    auto transaction_new = std::make_unique<Transaction>(std::move(inputs),std::move(outputs));

    ASSERT_TRUE(db->validate_transaction(*transaction_new));
}