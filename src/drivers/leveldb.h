#ifndef KVFS_LEVELDB_H
#define KVFS_LEVELDB_H

#include <string>
#include <memory>

#include <leveldb/db.h>

class LevelDBDriver {
public:
    LevelDBDriver(const std::string path);

private:
    std::shared_ptr<leveldb::DB*> _db;
    leveldb::Options _options;
    leveldb::Status _status;
};

#endif //KVFS_LEVELDB_H
