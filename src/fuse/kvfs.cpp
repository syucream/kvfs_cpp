#include <fuse.h>

static struct fuse_operation kvfs_operation = {
};

int main(int argc, char *argv[]) {
    const auto args = FUSE_ARGS_INIT(argc, argv);

    const auto ret = fuse_main(args.argc, args.argv, &kvfs_operation, NULL);
    fuse_opt_free_args(&args);
    return ret;
}
