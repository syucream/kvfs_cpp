#include "leveldb.h"

using std::string;
using std::experimental::optional;

LevelDBDriver::LevelDBDriver(const string path) {
    leveldb::DB *db = nullptr;

    this->_options.create_if_missing = true;
    this->_status = leveldb::DB::Open(this->_options, path, &db);
    this->_db = std::make_shared<leveldb::DB*>(db);
}

optional<Content> LevelDBDriver::read(const string key) {
    string value;

    const auto status = (*this->_db)->Get(leveldb::ReadOptions(), leveldb::Slice(key), &value);
    if (status.IsNotFound()) {
        return std::experimental::nullopt;
    }

    return std::experimental::make_optional(Content(value.data(), value.size()));
}

bool LevelDBDriver::exist(const std::string key) {
    return this->read(key) != std::experimental::nullopt;
}