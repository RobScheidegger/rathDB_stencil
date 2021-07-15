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

TEST(Chain, HandleBlockMultipleStack){
    std::filesystem::remove_all(ChainWriter::get_data_directory());

    Chain chain = Chain();

    std::unique_ptr<Block> genesis_block = chain.get_last_block();

    const int NUM = 10;
    for(int i = 0; i < NUM; i++){
        std::unique_ptr<Block> last_block = chain.get_last_block();
        std::unique_ptr<Block> new_block = make_blockd(std::move(last_block), 0, 0);
        auto block_hash = RathCrypto::hash(Block::serialize(*new_block));
        auto transaction_hash = RathCrypto::hash(Transaction::serialize(*new_block->transactions.at(0)));
        std::cout << "Expected Hash: " << block_hash << " with transaction " << transaction_hash << std::endl;
        EXPECT_EQ(new_block->transactions.size(), 1);
        EXPECT_EQ(new_block->transactions.at(0)->transaction_outputs.size(), 1);
        EXPECT_EQ(new_block->transactions.at(0)->transaction_inputs.size(), 1);
        chain.handle_block(std::move(new_block));
        EXPECT_EQ(chain.get_last_block_hash(), block_hash);
    }

    auto blocks = chain.get_active_chain_hashes(1,NUM);
    EXPECT_EQ(blocks.size(), NUM);
    EXPECT_EQ(chain.get_active_chain_length(), NUM + 1);
}

TEST(Chain, PersistsTransactionHash){
    std::filesystem::remove_all(ChainWriter::get_data_directory());

    Chain chain = Chain();

    std::unique_ptr<Block> genesis_block = chain.get_last_block();
    std::unique_ptr<Block> new_block = make_blockd(std::move(genesis_block), 0, 0);
    auto block_hash = RathCrypto::hash(Block::serialize(*new_block));
    auto transaction_hash = RathCrypto::hash(Transaction::serialize(*new_block->transactions.at(0)));
    // auto last_transaction = new_block->transactions.at(0);
    chain.handle_block(std::move(new_block));

    std::unique_ptr<Block> added_block = chain.get_last_block();
    auto new_hash = RathCrypto::hash(Block::serialize(*added_block));
    auto new_transaction_hash = RathCrypto::hash(Transaction::serialize(*added_block->transactions.at(0)));

    EXPECT_EQ(block_hash, new_hash);
    EXPECT_EQ(transaction_hash, new_transaction_hash);

}

TEST(Chain, ForkedBlock){
    std::filesystem::remove_all(ChainWriter::get_data_directory());

    Chain chain = Chain();

    std::unique_ptr<Block> genesis_block = chain.get_last_block();
    std::unique_ptr<Block> new_block = make_blockd(std::move(genesis_block), 0, 0);
    std::unique_ptr<Block> genesis_block_2 = chain.get_last_block();
    std::unique_ptr<Block> new_block_2 = make_blockd(std::move(genesis_block_2), 0, 1);
    auto block_hash = RathCrypto::hash(Block::serialize(*new_block));
    auto block_hash_2 = RathCrypto::hash(Block::serialize(*new_block_2));
    // auto last_transaction = new_block->transactions.at(0);
    chain.handle_block(std::move(new_block));
    std::unique_ptr<Block> added_block = chain.get_last_block();
    auto new_hash = RathCrypto::hash(Block::serialize(*added_block));
    EXPECT_EQ(block_hash, new_hash);

    chain.handle_block(std::move(new_block_2));

    std::unique_ptr<Block> current_head = chain.get_last_block();
    auto current_hash = RathCrypto::hash(Block::serialize(*current_head));
    EXPECT_EQ(current_hash, block_hash);
}


TEST(Chain, ForkedBlockTakeOverMainChain){
    std::filesystem::remove_all(ChainWriter::get_data_directory());

    Chain chain = Chain();

    std::unique_ptr<Block> genesis_block = chain.get_last_block();
    std::unique_ptr<Block> new_block = make_blockd(std::move(genesis_block), 0, 0);
    std::unique_ptr<Block> genesis_block_2 = chain.get_last_block();
    std::unique_ptr<Block> new_block_2 = make_blockd(std::move(genesis_block_2), 0, 1);
    auto new_block_copy = Block::deserialize(Block::serialize(*new_block_2));
    std::unique_ptr<Block> forked_block = make_blockd(std::move(new_block_copy), 0, 0);
    auto block_hash = RathCrypto::hash(Block::serialize(*new_block));
    auto forked_block_hash = RathCrypto::hash(Block::serialize(*forked_block));

    chain.handle_block(std::move(new_block));
    auto new_hash = chain.get_last_block_hash();
    EXPECT_EQ(block_hash, new_hash);

    chain.handle_block(std::move(new_block_2));

    auto current_hash = chain.get_last_block_hash();
    EXPECT_EQ(current_hash, block_hash);

    chain.handle_block(std::move(forked_block));

    auto current_head = chain.get_last_block_hash();
    EXPECT_EQ(chain.get_last_block_hash(), forked_block_hash);
}