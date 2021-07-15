/*
 * This file belongs to Brown University's computer
 * science department as part of csci1951L - Blockchains
 * and cryptocurrencies.
 *
 * This software was developed by Colby Anderson (HTA)
 * and Parker Ljung (TA) of csci1951L in Summer of 2021.
 */

#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

#include <gtest/gtest.h>
#include <chain.h>
#include <rathcrypto.h>
#include <filesystem>
#include <memory>

TEST(Chain, GetGenesisBlockHash0) {
    // test setup - remove past data
    std::filesystem::remove_all(ChainWriter::get_data_directory());

    Chain chain = Chain();

    std::unique_ptr<Block> genesis_block = chain.get_last_block();
    // check that genesis block has at least 1 transaction
    EXPECT_TRUE(genesis_block->transactions.size() >= 1);
    const std::vector<std::unique_ptr<TransactionOutput>> &transaction_outputs = genesis_block->transactions.at(0)->transaction_outputs;
    // check that the first transaction has at least 3 outputs
    EXPECT_TRUE(transaction_outputs.size() >= 3);
    EXPECT_EQ(transaction_outputs.at(0)->amount, 100);
    EXPECT_EQ(transaction_outputs.at(1)->amount, 200);
    EXPECT_EQ(transaction_outputs.at(2)->amount, 300);

    uint32_t hash0 = RathCrypto::hash(Block::serialize(*genesis_block));
    EXPECT_EQ(hash0, chain.get_last_block_hash());

    std::filesystem::remove_all(ChainWriter::get_data_directory());

}

std::unique_ptr<Block> make_blockd(std::unique_ptr<Block> block, int tx_index, int out_index) {
    std::vector<std::unique_ptr<Transaction>> transactions;
    std::vector<std::unique_ptr<TransactionInput>> transaction_inputs;
    transaction_inputs.push_back(std::make_unique<TransactionInput>(
            RathCrypto::hash(Transaction::serialize(*block->transactions.at(tx_index))),
            out_index,
            99
    ));
    std::vector<std::unique_ptr<TransactionOutput>> transaction_outputs;
    transaction_outputs.push_back(std::make_unique<TransactionOutput>(
    block->transactions.at(tx_index)->transaction_outputs.at(out_index)->amount,
        block->transactions.at(tx_index)->transaction_outputs.at(out_index)->public_key
    ));
    transactions.push_back(std::make_unique<Transaction>(std::move(transaction_inputs), std::move(transaction_outputs)));
    std::unique_ptr<BlockHeader> block_header = std::make_unique<BlockHeader>(1, RathCrypto::hash(Block::serialize(*block)), 3, 4, 5, 6);
    std::unique_ptr<Block> b = std::make_unique<Block>( std::move(block_header), std::move(transactions));
    return std::move(b);
}

TEST(Chain, HandleValidBlock23) {
    std::filesystem::remove_all(ChainWriter::get_data_directory());

    Chain chain = Chain();

    // 1 = add valid to genesis
    std::unique_ptr<Block> genesis_block = chain.get_last_block();
    // check that genesis block has at least 1 transaction
    EXPECT_TRUE(genesis_block->transactions.size() >= 1);
    const std::vector<std::unique_ptr<TransactionOutput>> &transaction_outputs = genesis_block->transactions.at(0)->transaction_outputs;
    // check that the first transaction has at least 3 outputs
    EXPECT_TRUE(transaction_outputs.size() >= 3);
    EXPECT_EQ(transaction_outputs.at(0)->amount, 100);
    EXPECT_EQ(transaction_outputs.at(1)->amount, 200);
    EXPECT_EQ(transaction_outputs.at(2)->amount, 300);
    std::unique_ptr<Block> block = make_blockd(std::move(genesis_block), 0, 0);
    uint32_t block_hash = RathCrypto::hash(Block::serialize(*block));
    chain.handle_block(std::move(block));

    EXPECT_EQ(block_hash, chain.get_last_block_hash());
    std::unique_ptr<Block> ret_block = chain.get_last_block();
    EXPECT_EQ(ret_block->transactions.size(), 1);
    EXPECT_EQ(ret_block->transactions.at(0)->transaction_outputs.size(), 1);
    EXPECT_EQ(ret_block->transactions.at(0)->transaction_outputs.at(0)->amount, 100);
}

TEST(Chain, GetActiveChainHashes1To1){
    std::filesystem::remove_all(ChainWriter::get_data_directory());

    Chain chain = Chain();

    auto hashes = chain.get_active_chain_hashes(1,1);
    EXPECT_EQ(hashes.size(), 1);
}

TEST(Chain, GetActiveChain1To1){
    std::filesystem::remove_all(ChainWriter::get_data_directory());

    Chain chain = Chain();

    auto blocks = chain.get_active_chain(1,1);
    EXPECT_EQ(blocks.size(), 1);
}

