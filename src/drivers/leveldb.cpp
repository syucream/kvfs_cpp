#include "leveldb.h"

using std::string;
using std::vector;
using std::experimental::optional;

LevelDBDriver::LevelDBDriver(const string path) {
    leveldb::DB *db = nullptr;

    this->_options.create_if_missing = true;

    // TODO check status, it might cause db initialization failure.
    leveldb::DB::Open(this->_options, path, &db);

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

optional<size_t> LevelDBDriver::write(const string& key, const Content &c) {
    const auto value = leveldb::Slice(c.data, c.size);
    const auto status = (*this->_db)->Put(leveldb::WriteOptions(), key, value);
    if (status.IsNotFound()) {
        return std::experimental::nullopt;
    }

    return std::experimental::make_optional(size_t(c.size));
}

bool LevelDBDriver::exist(const std::string key) {
    return this->read(key) != std::experimental::nullopt;
}

vector<string> LevelDBDriver::keys(const std::string partial_key) {
    vector<string> keys;

    auto it = (*this->_db)->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        const auto s = it->key();
        const auto k = string(s.data(), s.size());
        if (k.find(partial_key) == 0) {
            keys.push_back(k);
        }
    }

    return keys;
}
