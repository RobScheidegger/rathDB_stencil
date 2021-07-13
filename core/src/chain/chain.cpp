#include <chain.h>
#include <rathcrypto.h>

Chain::Chain() : _active_chain_length(1),
    _active_chain_last_block(construct_genesis_block()),
    _block_info_database(std::make_unique<BlockInfoDatabase>()),
    _coin_database(std::make_unique<CoinDatabase>()),
    _chain_writer(std::make_unique<ChainWriter>()) {

    const UndoBlock undo_genesis_block = make_undo_block(std::move(_active_chain_last_block));

    const FileInfo& block_info = *_chain_writer->write_block(Block::serialize(*_active_chain_last_block));
    const FileInfo& undo_block_info = *_chain_writer->write_block(UndoBlock::serialize(undo_genesis_block));

    const auto block_record = new BlockRecord(std::move(_active_chain_last_block->block_header),
                                         _active_chain_last_block->transactions.size(),
                                         0,
                                         block_info,
                                         undo_block_info);

    _block_info_database->store_block_record(RathCrypto::hash(BlockRecord::serialize(*block_record)),*block_record);

    _coin_database->store_block(std::move(_active_chain_last_block->transactions));
}



UndoBlock Chain::make_undo_block(std::unique_ptr<Block> original_block){

}

void Chain::handle_block(std::unique_ptr<Block> block) {
    // If block is going to active chain
    bool validated = this->_coin_database->validate_block(block->transactions);
    bool appended_to_active_chain = block->block_header->previous_block_hash == this->get_last_block_hash();
    if(validated && appended_to_active_chain){
        // On the main chain, so store in coin_database
        this->_coin_database->store_block(block->transactions);
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
        auto undoBlock = make_undo_block(std::move(block));

        const FileInfo& block_file_info =  *_chain_writer->write_block(Block::serialize(*block));
        const FileInfo& undoblock_file_info =  *_chain_writer->write_block(UndoBlock::serialize(undoBlock));

        /*
        const auto& block_record = new BlockRecord(std::move(block->block_header),
                                                  block->transactions.size(),
                                                  height,
                                                  block_file_info,
                                                  undoblock_file_info);
       */
        _chain_writer->store_block(*block, height);

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

        }

    }

}
