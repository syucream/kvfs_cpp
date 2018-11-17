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

// TODO Separate basic decleartions to an interface.
class LevelDBDriver {
public:
    LevelDBDriver(const std::string path);

    bool connect();

    std::experimental::optional<Content> read(const std::string key);

    std::experimental::optional<size_t> write(const std::string& key, const Content& c);

    bool exist(const std::string key);

    std::vector<std::string> keys(const std::string partial_key);

private:
    std::shared_ptr<leveldb::DB *> _db;
    leveldb::Options _options;
};

#endif //KVFS_LEVELDB_H
