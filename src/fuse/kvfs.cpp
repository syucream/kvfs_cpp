#include <string>
#include <cerrno>
#include <cstring>

#include <fuse.h>

#include "../drivers/leveldb.h"

using std::string;

constexpr auto stat_size = sizeof(struct stat);

// TODO ensure thread safety, and define an interface
LevelDBDriver *driver;

static int kvfs_getattr(const char *path,
                        struct stat *stbuf) {

    const auto path_str = string(path);

    memset(stbuf, 0, stat_size);

    // TODO

    return -ENOENT;
}

static int kvfs_readdir(const char *path,
                        void *buf,
                        fuse_fill_dir_t filler,
                        off_t offset,
                        struct fuse_file_info *fi) {

    // TODO

    return 0;
}

static int kvfs_open(const char *path,
                     struct fuse_file_info *fi) {

    driver = new LevelDBDriver(string(path));

    return 0;
}

static int kvfs_read(const char *path,
                     char *buf,
                     size_t size,
                     off_t offset,
                     struct fuse_file_info *fi) {
    // TODO

    return 0;
}

const static struct fuse_operations kvfs_operation = {
        .getattr = kvfs_getattr,
        .readdir = kvfs_readdir,
        .open = kvfs_open,
        .read = kvfs_read,
};

int main(int argc, char **argv) {
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    const auto ret = fuse_main(args.argc, args.argv, &kvfs_operation, nullptr);
    fuse_opt_free_args(&args);

    return ret;
}
