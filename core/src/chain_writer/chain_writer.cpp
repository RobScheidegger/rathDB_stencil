#include <chain_writer.h>
#include <filesystem>

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

std::unique_ptr<BlockRecord> ChainWriter::store_block(const Block &block, const UndoBlock &undo_block, uint32_t height) {
    std::unique_ptr<FileInfo> block_info = write_block(Block::serialize(block));
    std::unique_ptr<FileInfo> undo_block_info = write_undo_block(UndoBlock::serialize(undo_block));

    auto block_header_copy = std::make_unique<BlockHeader>(
            block.block_header->version,
            block.block_header->previous_block_hash,
            block.block_header->merkle_root,
            block.block_header->difficulty_target,
            block.block_header->nonce,
            block.block_header->timestamp
            );
    auto num_transactions = block.transactions.size();
    auto record = new BlockRecord(std::move(block_header_copy),
                                                num_transactions,
                                                height,
                                                *block_info.get(),
                                                *undo_block_info.get());
    std::unique_ptr<BlockRecord> unique_record(record);
    return std::move(unique_record);

}

std::unique_ptr<FileInfo> ChainWriter::write_block(std::string serialized_block) {
    // Add one to account for extra char offset
    auto block_length = serialized_block.size() + 1;

    if(_current_block_offset + block_length >= get_max_block_file_size())
    {
        // Need to write to a new file
        _current_block_file_number++;
        _current_block_offset = 0;
    }
    const std::string file_to_write = get_data_directory() + "/" +
            get_block_filename() + "_" +
            std::to_string(_current_block_file_number) + "." +
            get_file_extension();

    const auto& write_file = file_to_write.c_str();
    auto file = fopen(write_file, "at");
    if(!std::filesystem::is_directory(get_data_directory()))
    {
        std::filesystem::create_directory(get_data_directory());
    }
    if(!file){
        file = fopen(write_file, "wt");
    }
    fwrite(serialized_block.c_str(), sizeof(char), block_length, file);
    fclose(file);

    _current_block_offset += block_length;
    auto fileInfo = new FileInfo(file_to_write, _current_block_offset - block_length , _current_block_offset);

    auto ptr = std::unique_ptr<FileInfo>(fileInfo);
    return ptr;
}

std::unique_ptr<FileInfo> ChainWriter::write_undo_block(std::string serialized_block) {
    auto block_length = serialized_block.size();

    if(_current_undo_offset + block_length >= get_max_block_file_size())
    {
        // Need to write to a new file
        _current_undo_file_number++;
        _current_undo_offset = 0;
    }

    std::string file_to_write = get_data_directory() + "/" +
                                get_undo_filename() + "_" +
                                std::to_string(_current_undo_file_number) + "." +
                                get_file_extension();

    const auto& write_file = file_to_write.c_str();
    auto file = fopen(write_file, "at");
    if(!std::filesystem::is_directory(get_data_directory()))
    {
        std::filesystem::create_directory(get_data_directory());
    }
    if(!file){
        file = fopen(write_file, "wt");
    }
    fwrite(serialized_block.c_str(), sizeof(char), block_length, file);
    fclose(file);

    _current_undo_offset += block_length;
    return std::make_unique<FileInfo>(file_to_write, _current_undo_offset - block_length , _current_undo_offset);
}

std::string ChainWriter::read_block(const FileInfo &block_location) {
    auto file = fopen(block_location.file_name.c_str(), "r");
    auto pos = fseek(file, block_location.start, SEEK_SET);
    auto size = block_location.end - block_location.start;
    char * buffer = (char*) malloc (sizeof(char)*size);
    fread(buffer, 1, size, file);
    fclose(file);
    std::string serialized_block(buffer, size);
    return serialized_block;
}

std::string ChainWriter::read_undo_block(const FileInfo& undo_block_location){
    return read_block(undo_block_location);
}





