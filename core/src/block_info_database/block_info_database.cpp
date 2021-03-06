#include <block_info_database.h>

BlockInfoDatabase::BlockInfoDatabase() {
    _database = std::make_unique<Database>();
}

void BlockInfoDatabase::store_block_record(uint32_t hash, const BlockRecord& record)
{
    _database->put_safely(std::to_string(hash), BlockRecord::serialize(record));
}

std::unique_ptr<BlockRecord> BlockInfoDatabase::get_block_record(uint32_t block_hash)
{
    auto hash_string = std::to_string(block_hash);
    if(!_database->contains(hash_string)){
        return nullptr;
    }
    auto serialized_record = _database->get_safely(hash_string);
    auto record = BlockRecord::deserialize(serialized_record);
    return std::move(record);
}