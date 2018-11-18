#ifndef KVFS_DRIVER_H
#define KVFS_DRIVER_H

#include <string>
#include <vector>
#include <experimental/optional>

struct Content {
    Content(const char *d, size_t s) {
        this->data = d;
        this->size = s;
    }

    const char *data;
    size_t size;
};

/**
 * A KVS DB's driver interface.
 *
 */
class Driver {
public:
    virtual ~Driver(){}

    virtual std::experimental::optional<Content> read(const std::string& key) = 0;

    virtual std::experimental::optional<size_t> write(const std::string& key, const Content& c) = 0;

    virtual bool exist(const std::string& key) = 0;

    virtual std::vector<std::string> keys(const std::string& partial_key) = 0;
};

#endif //KVFS_DRIVER_H
