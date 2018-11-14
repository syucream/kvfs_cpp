#include <memory>
#include "kvfs.h"

int main(int argc, char **argv) {
    const auto runner = std::shared_ptr<FuseRunner>(new FuseRunner(argc, argv));

    return runner->run();
}
