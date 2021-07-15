/*
 * This file belongs to Brown University's computer
 * science department as part of csci1951L - Blockchains
 * and cryptocurrencies.
 *
 * This software was developed by Colby Anderson (HTA)
 * and Parker Ljung (TA) of csci1951L in Summer of 2021.
 */

#include <gtest/gtest.h>
#include <chain.h>
#include <chain_writer.h>
#include <rathcrypto.h>
#include <filesystem>
#include <memory>

TEST(ChainWriter, WritesReadsBlock) {

    std::filesystem::remove_all(ChainWriter::get_data_directory());

    std::unique_ptr<ChainWriter> writer = std::make_unique<ChainWriter>();

    std::vector<std::unique_ptr<TransactionInput>> inputs;
    inputs.push_back(std::move(std::make_unique<TransactionInput>(0, 1, 0)));

    std::vector<std::unique_ptr<TransactionOutput>> outputs;
    outputs.push_back(std::move(std::make_unique<TransactionOutput>(0,1)));

    std::vector<std::unique_ptr<Transaction>> transactions;
    transactions.push_back(std::move(std::make_unique<Transaction>(std::move(inputs),std::move(outputs))));

    std::unique_ptr<Block> block = std::make_unique<Block>(
            std::make_unique<BlockHeader>(0,0,0,0,0,0),
            std::move(transactions)
            );

    // Create test block
    auto info = writer->write_block(Block::serialize(*block));

    auto serialized_block = writer->read_block(*info);

    auto result_block = Block::deserialize(serialized_block);

    std::cerr << BlockHeader::serialize(*result_block->block_header);
    EXPECT_EQ(Block::serialize(*result_block), Block::serialize(*block));

}

TEST(ChainWriter, WritesReadsMultiple) {

    std::filesystem::remove_all(ChainWriter::get_data_directory());

    std::unique_ptr<ChainWriter> writer = std::make_unique<ChainWriter>();

    std::vector<std::unique_ptr<TransactionInput>> inputs;
    inputs.push_back(std::move(std::make_unique<TransactionInput>(0, 1, 0)));

    std::vector<std::unique_ptr<TransactionOutput>> outputs;
    outputs.push_back(std::move(std::make_unique<TransactionOutput>(0,1)));
    outputs.push_back(std::move(std::make_unique<TransactionOutput>(31,1)));

    std::vector<std::unique_ptr<Transaction>> transactions;
    transactions.push_back(std::move(std::make_unique<Transaction>(std::move(inputs),std::move(outputs))));

    std::unique_ptr<Block> block = std::make_unique<Block>(
            std::make_unique<BlockHeader>(0,0,0,0,0,0),
            std::move(transactions)
    );

    std::vector<std::unique_ptr<TransactionInput>> inputs_2;
    inputs_2.push_back(std::move(std::make_unique<TransactionInput>(0, 1, 0)));

    std::vector<std::unique_ptr<TransactionOutput>> outputs_2;
    outputs_2.push_back(std::move(std::make_unique<TransactionOutput>(0,1)));
    outputs_2.push_back(std::move(std::make_unique<TransactionOutput>(31,1)));

    std::vector<std::unique_ptr<Transaction>> transactions_2;
    transactions_2.push_back(std::move(std::make_unique<Transaction>(std::move(inputs_2),std::move(outputs_2))));

    std::unique_ptr<Block> block_2 = std::make_unique<Block>(
            std::make_unique<BlockHeader>(3,10,2,0,0,0),
            std::move(transactions)
    );

    // Create test block
    auto info = writer->write_block(Block::serialize(*block));
    auto info_2 = writer->write_block(Block::serialize(*block_2));

    auto serialized_block = writer->read_block(*info);
    auto serialized_block_2 = writer->read_block(*info_2);

    auto result_block = Block::deserialize(serialized_block);
    auto result_block_2 = Block::deserialize(serialized_block_2);

    std::cerr << BlockHeader::serialize(*result_block->block_header);
    EXPECT_EQ(Block::serialize(*result_block), Block::serialize(*block));
    EXPECT_EQ(Block::serialize(*result_block_2), Block::serialize(*block_2));
}