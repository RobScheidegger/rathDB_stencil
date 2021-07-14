#include <chain_writer.h>

const std::string ChainWriter::_file_extension = "data";
const std::string ChainWriter::_block_filename = "blocks";
const uint16_t ChainWriter::_max_block_file_size = 1000;
const std::string ChainWriter::_undo_filename = "undo_blocks";
const uint16_t ChainWriter::_max_undo_file_size = 1000;
const std::string ChainWriter::_data_directory = "data";

ChainWriter::ChainWriter() : _current_block_file_number(0),
                            _current_block_offset(0),
                            _current_undo_file_number(0),
                            _current_undo_offset(0) {}

std::string ChainWriter::read_undo_block(const FileInfo &undo_block_location) {
    return std::string();
}

std::unique_ptr<BlockRecord> ChainWriter::store_block(const Block &block, const UndoBlock &undo_block, uint32_t height) {
    const FileInfo& block_info = *write_block(Block::serialize(block));
    const FileInfo& undo_block_info = *write_block(UndoBlock::serialize(undo_block));

    auto block_header_copy = std::make_unique<BlockHeader>(
            block.block_header->version,
            block.block_header->previous_block_hash,
            block.block_header->merkle_root,
            block.block_header->difficulty_target,
            block.block_header->nonce,
            block.block_header->timestamp
            );
    return std::make_unique<BlockRecord>(std::move(block_header_copy),
                                          block.transactions.size(),
                                          0,
                                          block_info,
                                          undo_block_info);

}



