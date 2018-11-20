#include <iostream>
#include <string>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <unistd.h>

#include "kvfs.h"

using std::string;
using std::shared_ptr;

constexpr auto stat_size = sizeof(struct stat);

// FIXME As a workaround
// TODO Ensure thread safety, and define an interface
shared_ptr<LevelDBDriver> driver;

struct kvfs_option {
    const char *path;
} options;

const struct fuse_opt kvfs_option_spec[] = {
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
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;  // TODO count subdir's
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
        stbuf->st_size = v->size;
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

    struct stat dir_st;
    dir_st.st_mode = S_IFDIR | 0755;
    dir_st.st_nlink = 2;

    // default dirs
    filler(buf, ".", &dir_st, 0);
    filler(buf, "..", &dir_st, 0);

    // keys
    struct stat file_st;
    file_st.st_mode = S_IFREG | 0444;
    file_st.st_nlink = 1;
    const auto keys = driver->keys(path_str);
    for (const auto k : keys) {
        filler(buf, k.data(), &file_st, 0);
    }

    return 0;
}

static int kvfs_open(const char *path,
                     struct fuse_file_info *fi) {
    if (!driver) {
        return -EIO;
    }

    const string spath(path);

    if (!driver->exist(spath)) {
        if (fi->flags & O_CREAT) {
            const auto wsize = driver->write(spath, Content(nullptr, 0));
            if (!wsize) {
                return -EIO;
            }
        } else {
            return -ENOENT;
        }
    }

    return 0;
}

static int kvfs_opendir(const char *path,
                        struct fuse_file_info *fi) {
    // TODO Check permission

    return 0;
}

static int kvfs_read(const char *path,
                     char *buf,
                     size_t size,
                     off_t offset,
                     struct fuse_file_info *fi) {
    if (!driver || !buf) {
        return -EIO;
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
        return -EIO;
    }

    const auto wsize = driver->write(string(path), Content(buf, size));
    if (!wsize) {
        return -ENOENT;
    }

    return *wsize;
}

static int kvfs_create(const char *path,
                       mode_t mode,
                       fuse_file_info *fi) {
    if (!driver) {
        return -EIO;
    }

    const auto wsize = driver->write(string(path), Content(nullptr, 0));
    if (!wsize) {
        return -EIO;
    }

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
        .opendir  = kvfs_opendir,
        .read     = kvfs_read,
        .write    = kvfs_write,
        .create   = kvfs_create,
        .access   = kvfs_access,
        .truncate = kvfs_truncate,
};

FuseRunner::FuseRunner(int argc, char **argv) {
    this->_args = FUSE_ARGS_INIT(argc, argv);

    options.path = "";
    if (fuse_opt_parse(&this->_args, &options, kvfs_option_spec, nullptr) == -1) {
        return;
    }
    std::cout << "path: " << options.path << std::endl;

    this->_driver = shared_ptr<LevelDBDriver>(new LevelDBDriver());

    if(!this->_driver->connect(string(options.path))) {
        std::cerr << "Couldn't connect the database" << std::endl;
        std::exit(1);
    }
}

FuseRunner::~FuseRunner() {
    fuse_opt_free_args(&this->_args);
}

int FuseRunner::run() {
    driver = this->_driver;
    return fuse_main(this->_args.argc, this->_args.argv, &kvfs_operation, nullptr);
}
