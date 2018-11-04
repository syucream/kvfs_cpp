#ifndef KVFS_LEVELDB_H
#define KVFS_LEVELDB_H

#include <memory>
#include <experimental/optional>
#include <string>
#include <vector>

#include <leveldb/db.h>

struct Content {
    Content(const char *d, size_t s) {
        this->data = d;
        this->size = s;
    }

    const char *data;
    size_t size;
};

class LevelDBDriver {
public:
    LevelDBDriver(const std::string path);

    std::experimental::optional<Content> read(const std::string key);

    bool exist(const std::string key);

private:
    std::shared_ptr<leveldb::DB *> _db;
    leveldb::Options _options;
    leveldb::Status _status;
};

#endif //KVFS_LEVELDB_H
