cmake_minimum_required(VERSION 3.10)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

project(kvfs)

set(kvfs_src
        src/fuse/kvfs.cpp
        src/drivers/leveldb.cpp
        )

set(kvfs_libs
        fuse
        leveldb
        )
add_executable(kvfs ${kvfs_src})
set_target_properties(kvfs PROPERTIES COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=29")
target_link_libraries(kvfs ${kvfs_libs})