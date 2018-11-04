#include <string>
#include <cerrno>
#include <cstring>

#include <fuse.h>

#include "../drivers/leveldb.h"

using std::string;

constexpr auto stat_size = sizeof(struct stat);

// TODO ensure thread safety, and define an interface
LevelDBDriver *driver = nullptr;

static struct kvfs_option {
    const char *path;
} options;

static const struct fuse_opt kvfs_option_spec[] = {
        {"--path=%s", offsetof(struct kvfs_option, path), 1}
};

static void *kvfs_init(struct fuse_conn_info *conn) {
    // TODO

    return nullptr;
}

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

    if (!driver->exist(string(path))) {
        return -ENOENT;
    }

    return 0;
}

static int kvfs_read(const char *path,
                     char *buf,
                     size_t size,
                     off_t offset,
                     struct fuse_file_info *fi) {
    if (!driver || !buf) {
        return -ENOENT;
    }

    const auto v = driver->read(string(path));
    if (!v || v->size < size) {
        return -ENOENT;
    }

    std::memcpy(buf, v->data, v->size);

    return v->size;
}

const static struct fuse_operations kvfs_operation = {
        .init    = kvfs_init,
        .getattr = kvfs_getattr,
        .readdir = kvfs_readdir,
        .open    = kvfs_open,
        .read    = kvfs_read,
};

int main(int argc, char **argv) {
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    options.path = "";
    if (fuse_opt_parse(&args, &options, kvfs_option_spec, nullptr) == -1) {
        return 1;
    }

    const auto ret = fuse_main(args.argc, args.argv, &kvfs_operation, nullptr);

    // TODO pass the path to db.
    driver = new LevelDBDriver(string(options.path));

    fuse_opt_free_args(&args);

    return ret;
}
