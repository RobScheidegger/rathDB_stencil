#include <chain.h>
#include <rathcrypto.h>

Chain::Chain() : _active_chain_length(1),
    _active_chain_last_block(construct_genesis_block()),
    _block_info_database(std::make_unique<BlockInfoDatabase>()),
    _coin_database(std::make_unique<CoinDatabase>()),
    _chain_writer(std::make_unique<ChainWriter>()) {

    auto undo_genesis_block = make_undo_block(*_active_chain_last_block);

    const auto block_record = _chain_writer->store_block(*_active_chain_last_block, *undo_genesis_block, 0);

    _block_info_database->store_block_record(RathCrypto::hash(BlockRecord::serialize(*block_record)),*block_record);

    auto duplicate_genesis_block = Block::deserialize(Block::serialize(*_active_chain_last_block));

    _coin_database->store_block(std::move(duplicate_genesis_block->transactions));

    _active_chain_length = 1;
}



std::unique_ptr<UndoBlock> Chain::make_undo_block(const Block& original_block){
    std::vector<uint32_t> transaction_hashes;
    std::vector<std::unique_ptr<UndoCoinRecord>> undo_coin_records;

    for(auto& transaction : original_block.transactions) {

        auto version = transaction->version;
        auto hash = RathCrypto::hash(Transaction::serialize(*transaction));
        transaction_hashes.push_back(hash);
        std::vector<uint32_t> utxo;
        std::vector<uint32_t> amounts;
        std::vector<uint32_t> public_keys;
        for(auto& input : transaction->transaction_inputs){
            // For each input, find the corresponding UTXO that it consumed and add to utxo, amts, public_keys
            auto txo = _coin_database->get_utxo(input->reference_transaction_hash, input->utxo_index);
            utxo.push_back(input->utxo_index);
            amounts.push_back(txo->amount);
            public_keys.push_back(txo->public_key);
        }
        auto undo_record = std::make_unique<UndoCoinRecord>(version,utxo,amounts,public_keys);
        undo_coin_records.push_back(std::move(undo_record));
    }
    return std::make_unique<UndoBlock>(std::move(transaction_hashes), std::move(undo_coin_records));
}

void Chain::handle_block(std::unique_ptr<Block> block) {
    // If block is going to active chain
    bool validated = this->_coin_database->validate_block(block->transactions);
    bool appended_to_active_chain = block->block_header->previous_block_hash == this->get_last_block_hash();
    if(validated && appended_to_active_chain){
        // On the main chain, so store in coin_database
        // Duplicate it so we don't move the original value
        auto copied_block = Block::deserialize(Block::serialize(*block));
        this->_coin_database->store_block(std::move(copied_block->transactions));
    }

    if (validated)
    {
        // Find the height of the block
        int height;
        if(appended_to_active_chain)
        {
            height = this->get_active_chain_length() + 1;
        }
        else {
            std::unique_ptr<BlockRecord> record = this->_block_info_database->get_block_record(block->block_header->previous_block_hash);
            height = record->height + 1;
        }
        // Create the necessary undoBlock
        auto undoBlock = make_undo_block(*block);

        _chain_writer->store_block(*block, *undoBlock, height);

        if(appended_to_active_chain)
        {
            this->_active_chain_length++;
            this->_active_chain_last_block.swap(block);
        }
        if(height > _active_chain_length)
        {
            // A fork has taken over the main chain, so have to undo that
            auto this_block_hash = RathCrypto::hash(Block::serialize(*block));
            auto forked_blocks = get_forked_blocks_stack(this_block_hash);
            auto get_undo_blocks_queue = this->get_undo_blocks_queue(forked_blocks.size());
            for (auto& undo_block : get_undo_blocks_queue){
                // Apply each undo block to the coin_database to reverse the utxo
                // TODO

            }
            for(auto& forked_block : forked_blocks){
                _coin_database->store_block(std::move(forked_block->transactions));
            }
        }
    }
}

void Chain::handle_transaction(std::unique_ptr<Transaction> transaction){
    _coin_database->validate_and_store_transaction(std::move(transaction));
}

uint32_t Chain::get_chain_length(uint32_t block_hash){
    auto block_record = _block_info_database->get_block_record(block_hash);
    if(block_record == NULL){
        return 0;
    }
    else return block_record->height;
}

std::unique_ptr<Block> Chain::get_block(uint32_t block_hash){
    // First, find the block record
    auto block_record = _block_info_database->get_block_record(block_hash);
    if (block_record == NULL){
        return nullptr;
    }
    auto file_info = new FileInfo(block_record->block_file_stored, block_record->block_offset_start, block_record->block_offset_end);
    auto serialized_block = _chain_writer->read_block(*file_info);
    auto block = Block::deserialize(serialized_block);
    return block;
}

std::vector<std::unique_ptr<Block>> Chain::get_active_chain(uint32_t start, uint32_t end) {
    std::vector<std::unique_ptr<Block>> return_vector;
    if(end < start)
        return return_vector;

    auto last_block_record = _block_info_database->get_block_record(RathCrypto::hash(Block::serialize(*_active_chain_last_block)));
    if(last_block_record->height <= end && last_block_record->height >= start)
    {
        auto height = last_block_record->height;
        std::unique_ptr<BlockRecord> previous_block_record = std::move(last_block_record);
        for(int i = height; i > start && i >= 0; i--){
            auto file_info = new FileInfo(previous_block_record->block_file_stored,
                                           previous_block_record->block_offset_start,
                                           previous_block_record->block_offset_end);
            auto serialized_block = _chain_writer->read_block(*file_info);
            auto block = Block::deserialize(serialized_block);
            previous_block_record = _block_info_database->get_block_record(block->block_header->previous_block_hash);
            return_vector.push_back(std::move(block));
        }
        return return_vector;
    }
    else return return_vector;
}

std::vector<uint32_t> Chain::get_active_chain_hashes(uint32_t start, uint32_t end){
    std::vector<uint32_t> return_vector;
    if(end < start)
        return return_vector;

    auto last_block_record = _block_info_database->get_block_record(RathCrypto::hash(Block::serialize(*_active_chain_last_block)));
    if(last_block_record->height <= end && last_block_record->height >= start)
    {
        auto height = last_block_record->height;
        std::unique_ptr<BlockRecord> previous_block_record = std::move(last_block_record);
        for(int i = height; i > start && i >= 0; i--){

            return_vector.push_back(previous_block_record->block_header->previous_block_hash);
            previous_block_record = _block_info_database->get_block_record(previous_block_record->block_header->previous_block_hash);
        }
        return return_vector;
    }
    else return return_vector;
}

std::unique_ptr<Block> Chain::get_last_block(){
    // Create a new block from scratch from _active_chain_last_block
    auto previous_header = *_active_chain_last_block->block_header;
    auto new_block_header = std::make_unique<BlockHeader>(
            previous_header.version,
            previous_header.previous_block_hash,
            previous_header.merkle_root,
            previous_header.difficulty_target,
            previous_header.nonce,
            previous_header.timestamp);
    std::vector<std::unique_ptr<Transaction>> new_transactions;

    for(auto& transaction : _active_chain_last_block->transactions){
        std::vector<std::unique_ptr<TransactionInput>> new_inputs;
        std::vector<std::unique_ptr<TransactionOutput>> new_outputs;
        for(auto& input : transaction->transaction_inputs){
            new_inputs.push_back(std::make_unique<TransactionInput>(input->reference_transaction_hash,
                                                                    input->signature,
                                                                    input->utxo_index));
        }
        for(auto& output : transaction->transaction_outputs){
            new_outputs.push_back(std::make_unique<TransactionOutput>(
                                                                    output->amount,
                                                                    output->public_key));
        }
        new_transactions.push_back(std::move(std::make_unique<Transaction>(
                std::move(new_inputs),
                std::move(new_outputs),
                transaction->version,
                transaction->lock_time
                )));
    }

    auto new_block = std::make_unique<Block>(std::move(new_block_header), std::move(new_transactions));
    return new_block;
}

uint32_t Chain::get_last_block_hash(){
    return RathCrypto::hash(Block::serialize(*_active_chain_last_block));
}

uint32_t Chain::get_active_chain_length() const{
    return _active_chain_length;
}

std::vector<std::shared_ptr<Block>> Chain::get_forked_blocks_stack(uint32_t starting_hash){
    std::vector<std::shared_ptr<Block>> return_blocks;
    auto next_hash = get_last_block_hash();
    // TODO

}

std::vector<std::unique_ptr<UndoBlock>> Chain::get_undo_blocks_queue(uint32_t branching_height){
    std::vector<std::unique_ptr<UndoBlock>> return_blocks;
    auto next_hash = get_last_block_hash();
    for(int i = get_active_chain_length(); i >= branching_height; i--){
        auto block_record = _block_info_database->get_block_record(next_hash);
        auto undo_file_info = new FileInfo(
                    block_record->undo_file_stored,
                    block_record->undo_offset_start,
                    block_record->undo_offset_end
                );
        auto undo_block_serialized = _chain_writer->read_undo_block(*undo_file_info);
        auto undo_block = UndoBlock::deserialize(undo_block_serialized);
        return_blocks.push_back(std::move(undo_block));
    }

    return return_blocks;
}

std::unique_ptr<Block> Chain::construct_genesis_block(){
    auto block_header = std::make_unique<BlockHeader>(1,0,0,0,0,0);

    auto output_1 = std::make_unique<TransactionOutput>(100, 12345);
    auto output_2 = std::make_unique<TransactionOutput>(200,67891);
    auto output_3 = std::make_unique<TransactionOutput>(300,23456);

    std::vector<std::unique_ptr<TransactionOutput>> outputs;
    std::vector<std::unique_ptr<TransactionInput>> inputs;
    std::vector<std::unique_ptr<Transaction>> transactions;
    outputs.push_back(std::move(output_1));
    outputs.push_back(std::move(output_2));
    outputs.push_back(std::move(output_3));

    auto transaction = std::make_unique<Transaction>(std::move(inputs), std::move(outputs),0,0);
    transactions.push_back(std::move(transaction));
    return std::make_unique<Block>(std::move(block_header), std::move(transactions));
}