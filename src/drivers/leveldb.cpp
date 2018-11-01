#include "leveldb.h"

using std::string;

LevelDBDriver::LevelDBDriver(const string path) {
    leveldb::DB *db = nullptr;

    this->_options.create_if_missing = true;
    this->_status = leveldb::DB::Open(this->_options, path, &db);
    this->_db = std::make_shared<leveldb::DB*>(db);
}

