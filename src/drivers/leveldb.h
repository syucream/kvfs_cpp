#ifndef KVFS_LEVELDB_H
#define KVFS_LEVELDB_H

#include <memory>
#include "../../include/driver.h"

#include <leveldb/db.h>


class LevelDBDriver : Driver {
public:
    LevelDBDriver();

    bool connect(const std::string& path);

    std::experimental::optional<Content> read(const std::string& key);

    std::experimental::optional<size_t> write(const std::string& key, const Content& c);

    bool exist(const std::string& key);

    std::vector<std::string> keys(const std::string& partial_key);

private:
    std::shared_ptr<leveldb::DB *> _db;
    leveldb::Options _options;
};

#endif //KVFS_LEVELDB_H
