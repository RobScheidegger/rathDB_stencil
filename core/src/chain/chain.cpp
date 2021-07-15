#include <chain.h>
#include <rathcrypto.h>

Chain::Chain() : _active_chain_length(1),
    _active_chain_last_block(construct_genesis_block()),
    _block_info_database(std::make_unique<BlockInfoDatabase>()),
    _coin_database(std::make_unique<CoinDatabase>()),
    _chain_writer(std::make_unique<ChainWriter>()) {

    auto genesis_block_hash = get_last_block_hash();
    auto undo_genesis_block = make_undo_block(*_active_chain_last_block);
    std::cout << "[Chain::constructor] Storing genesis block with hash: " << genesis_block_hash << std::endl;
    const auto block_record = _chain_writer->store_block(*_active_chain_last_block, *undo_genesis_block, 1);


    _block_info_database->store_block_record(genesis_block_hash,*block_record);

    _coin_database->store_block(_active_chain_last_block->get_transactions());

    _active_chain_length = 1;
}



std::unique_ptr<UndoBlock> Chain::make_undo_block(const Block& original_block){
    auto hash = RathCrypto::hash(Block::serialize(original_block));
    std::cout << "[Chain::make_undo_block] Making undo block for " << hash << std::endl;
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

    auto this_block_hash = RathCrypto::hash(Block::serialize(*block));
    std::cout << "[Chain::handle_block] Handling Block:" << this_block_hash << std::endl;
    // If block is going to active chain
    bool validated = this->_coin_database->validate_block(block->get_transactions());
    bool appended_to_active_chain = block->block_header->previous_block_hash == this->get_last_block_hash();
    if(validated && appended_to_active_chain){
        // On the main chain, so store in coin_database
        // Duplicate it so we don't move the original value
        this->_coin_database->store_block(block->get_transactions());
    }
    if(appended_to_active_chain){
        std::cout << "[Chain::handle_block] Block: " << this_block_hash << " going to main chain" << std::endl;
    }
    else {
        std::cout << "[Chain::handle_block] Block: " << this_block_hash << " not going to main chain" << std::endl;
    }

    if (validated || !appended_to_active_chain)
    {
        std::cout << "[Chain::handle_block] Block: " << this_block_hash << " to be stored" << std::endl;
        // Find the height of the block
        int height;
        if(appended_to_active_chain)
        {
            height = this->get_active_chain_length() + 1;
        }
        else {
            auto previous_hash = block->block_header->previous_block_hash;
            std::cout << "[Chain::handle_block] Looking for previous block " << previous_hash << std::endl;
            std::unique_ptr<BlockRecord> record = _block_info_database->get_block_record(previous_hash);
            if(record == nullptr){
                std::cout << "[Chain::handle_block] Error: Could not find block record for " << block->block_header->previous_block_hash << std::endl;
                return;
            }
            height = record->height + 1;
        }
        // Create the necessary undoBlock
        auto undoBlock = make_undo_block(*block);

        std::cout << "[Chain::handle_block] Storing Block: " << this_block_hash << " to disk" << std::endl;
        auto block_record =_chain_writer->store_block(*block, *undoBlock, height);
        std::cout << "[Chain::handle_block] Storing Block Record for " << this_block_hash << " to BlockInfoDatabase" << std::endl;
        //Also add it to the block info database
        _block_info_database->store_block_record(this_block_hash, *block_record);

        if(appended_to_active_chain)
        {
            this->_active_chain_length++;
            this->_active_chain_last_block = std::move(block);
        }
        if(height > _active_chain_length)
        {
            // A fork has taken over the main chain, so have to undo that
            std::cout << "[Chain::handle_block] Block: " << this_block_hash << " created override fork" << std::endl;
            auto forked_blocks = get_forked_blocks_stack(this_block_hash);
            auto undo_blocks = this->get_undo_blocks_queue(forked_blocks.size());

            _coin_database->undo_coins(std::move(undo_blocks));

            for(auto& forked_block : forked_blocks){
                auto forked_hash = RathCrypto::hash(Block::serialize(*forked_block));
                std::cout << "[Chain::handle_block] Storing Block " << forked_hash << " to CoinDatabase" << std::endl;
                _coin_database->store_block(forked_block->get_transactions());
            }
        }
    }
    else{
        std::cout << "[Chain::handle_block] Block: " << this_block_hash << " invalid." << std::endl;
    }
}

void Chain::handle_transaction(std::unique_ptr<Transaction> transaction){
    auto transaction_hash = RathCrypto::hash(Transaction::serialize(*transaction));
    std::cout << "[Chain::handle_transaction] Handling transaction: " << transaction_hash << std::endl;
    _coin_database->validate_and_store_transaction(std::move(transaction));
}

uint32_t Chain::get_chain_length(uint32_t block_hash){
    std::cout << "[Chain::get_chain_length] Getting Chain length for block " << block_hash << std::endl;
    auto block_record = _block_info_database->get_block_record(block_hash);
    if(block_record == NULL){
        std::cout << "[Chain::get_chain_length] Block " << block_hash << " not found" << std::endl;
        return 0;
    }
    else return block_record->height;
}

std::unique_ptr<Block> Chain::get_block(uint32_t block_hash){
    // First, find the block record
    std::cout << "[Chain::get_block] Getting Block For:" << block_hash << std::endl;
    auto block_record = _block_info_database->get_block_record(block_hash);
    if (block_record == NULL){
        std::cout << "[Chain::get_block] No record found for:" << block_hash << std::endl;
        return nullptr;
    }
    auto file_info = new FileInfo(block_record->block_file_stored, block_record->block_offset_start, block_record->block_offset_end);
    auto serialized_block = _chain_writer->read_block(*file_info);
    auto block = Block::deserialize(serialized_block);
    return block;
}

std::vector<std::unique_ptr<Block>> Chain::get_active_chain(uint32_t start, uint32_t end) {
    std::cout << "[Chain::get_active_chain] Getting active chain from " << start << " to " << end << std::endl;
    std::vector<std::unique_ptr<Block>> return_vector;
    if(end < start)
        return return_vector;

    auto last_block_record = _block_info_database->get_block_record(RathCrypto::hash(Block::serialize(*_active_chain_last_block)));
    if(last_block_record->height <= end && last_block_record->height >= start)
    {
        auto height = last_block_record->height;
        std::unique_ptr<BlockRecord> previous_block_record = std::move(last_block_record);
        for(int i = height; i >= start && i >= 0; i--){
            auto file_info = new FileInfo(previous_block_record->block_file_stored,
                                           previous_block_record->block_offset_start,
                                           previous_block_record->block_offset_end);
            auto serialized_block = _chain_writer->read_block(*file_info);
            auto block = Block::deserialize(serialized_block);
            previous_block_record = _block_info_database->get_block_record(block->block_header->previous_block_hash);
            return_vector.push_back(std::move(block));
        }
        std::reverse(return_vector.begin(), return_vector.end());
        return return_vector;
    }
    else return return_vector;
}

std::vector<uint32_t> Chain::get_active_chain_hashes(uint32_t start, uint32_t end){
    std::cout << "[Chain::get_active_chain_hashes] Getting active hashes from " << start << " to " << end << std::endl;
    std::vector<uint32_t> return_vector;
    if(end < start)
        return return_vector;

    auto last_hash = RathCrypto::hash(Block::serialize(*_active_chain_last_block));
    std::cout << "[Chain::get_active_chain_hashes] Getting record for " << last_hash << std::endl;
    auto last_block_record = _block_info_database->get_block_record(last_hash);

    if(last_block_record == nullptr){
        std::cout << "[Chain::get_active_chain_hashes] Something went terribly wrong: "
                     "record for active chain last block not found " << std::endl;
    }
    std::cout << "[Chain::get_active_chain_hashes] Starting main height: " << last_block_record->height << std::endl;
    int current_height = last_block_record->height;
    auto current_hash = last_hash;
    while(current_height >= start) {
        if (current_height <= end){
            return_vector.push_back(current_hash);
        }
        std::cout << "[Chain::get_active_chain_hashes] Getting record for " << current_hash << " at height " << current_height << std::endl;
        auto current_record = _block_info_database->get_block_record(current_hash);

        current_hash = current_record->block_header->previous_block_hash;
        current_height--;
    }
    if(last_block_record->height <= end && last_block_record->height >= start)
    {
        auto height = last_block_record->height;
        std::unique_ptr<BlockRecord> previous_block_record = std::move(last_block_record);
        for(int i = height; i >= start && i >= 1; i--){


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
    std::cout << "[Chain::get_forked_blocks_stack] Getting stack from " << starting_hash << std::endl;
    std::vector<std::shared_ptr<Block>> return_blocks;

    auto main_chain_hashes = get_active_chain_hashes(_active_chain_length - 7, _active_chain_length);
    std::set<uint32_t> hashes_set;
    for(uint32_t hash : main_chain_hashes){
        hashes_set.insert(hash);
    }
    uint32_t next_hash = starting_hash;
    while(!hashes_set.contains(next_hash)){
        auto record = _block_info_database->get_block_record(next_hash);
        auto fileInfo = new FileInfo(record->block_file_stored, record->block_offset_start, record->block_offset_end);
        auto block = Block::deserialize(_chain_writer->read_block(*fileInfo));
        return_blocks.push_back(std::move(block));
    }

    return return_blocks;
}

std::vector<std::unique_ptr<UndoBlock>> Chain::get_undo_blocks_queue(uint32_t branching_height){
    std::cout << "[Chain::get_undo_blocks_queue] Getting undo blocks for height: " << branching_height << std::endl;
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