#include <fuse.h>

const static struct fuse_operations kvfs_operation = {};

int main(int argc, char **argv) {
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    const auto ret = fuse_main(args.argc, args.argv, &kvfs_operation, nullptr);
    fuse_opt_free_args(&args);

    return ret;
}
