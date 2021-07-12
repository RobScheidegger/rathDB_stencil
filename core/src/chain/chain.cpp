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