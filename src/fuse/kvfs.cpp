#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>
#include <unistd.h>

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
    const auto st_times = stbuf->st_ctime - time(nullptr);

    memset(stbuf, 0, stat_size);

    if (path_str.back() == '/') {
        // dir
        const auto keys = driver->keys(path_str);
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
        stbuf->st_uid = getuid();
        stbuf->st_gid = getgid();
        stbuf->st_atime = st_times;
        stbuf->st_mtime = st_times;
    } else {
        // file
        const auto v = driver->read(string(path));
        if (!v) {
            return -ENOENT;
        }
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_uid = getuid();
        stbuf->st_gid = getgid();
        stbuf->st_atime = st_times;
        stbuf->st_mtime = st_times;
    }

    return 0;
}

static int kvfs_readdir(const char *path,
                        void *buf,
                        fuse_fill_dir_t filler,
                        off_t offset,
                        struct fuse_file_info *fi) {
    const auto path_str = string(path);

    // It's a dir or not.
    if (path_str.back() != '/') {
        return -ENOENT;
    }

    // default dirs
    filler(buf, ".", nullptr, 0);
    filler(buf, "..", nullptr, 0);

    // keys
    const auto keys = driver->keys(path_str);
    for (const auto k : keys) {
        filler(buf, k.data(), nullptr, 0);
    }

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

static int kvfs_write(const char *path,
                      const char *buf,
                      size_t size,
                      off_t offset,
                      struct fuse_file_info *fi) {
    if (!driver || !buf) {
        return -ENOENT;
    }

    const auto wsize = driver->write(string(path), Content(buf, size));
    if (!size) {
        return -ENOENT;
    }

    return *wsize;
}

static int kvfs_create(const char *path,
                       mode_t mode,
                       fuse_file_info *fi) {
    // TODO

    return 0;
}

static int kvfs_access(const char *path,
                       int n) {
    // TODO

    return 0;
}

static int kvfs_truncate(const char *path,
                         off_t size) {
    // TODO

    return 0;
}

const static struct fuse_operations kvfs_operation = {
        .init     = kvfs_init,
        .getattr  = kvfs_getattr,
        .readdir  = kvfs_readdir,
        .open     = kvfs_open,
        .read     = kvfs_read,
        .write    = kvfs_write,
        .create   = kvfs_create,
        .access   = kvfs_access,
        .truncate = kvfs_truncate,
};

int main(int argc, char **argv) {
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    options.path = "";
    if (fuse_opt_parse(&args, &options, kvfs_option_spec, nullptr) == -1) {
        return 1;
    }
    std::cout << "path: " << options.path << std::endl;

    // For debug
    // fuse_opt_add_arg(&args, "-odefault_permissions");

    driver = new LevelDBDriver(string(options.path));
    const auto ret = fuse_main(args.argc, args.argv, &kvfs_operation, nullptr);

    fuse_opt_free_args(&args);

    return ret;
}
