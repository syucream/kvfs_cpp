#ifndef KVFS_KVFS_H
#define KVFS_KVFS_H

#include <fuse.h>
#include "../drivers/leveldb.h"

class FuseRunner {
public:
    FuseRunner(int argc, char **argv);
    ~FuseRunner();

    int run();

private:
    // TODO Support other DB's
    std::shared_ptr<LevelDBDriver> _driver;

    struct fuse_args _args;
};

#endif //KVFS_KVFS_H
