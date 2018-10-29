cmake_minimum_required(VERSION 3.10)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

project(KVFS)

set(kvfs_src
        src/fuse/kvfs.cpp
)

add_executable(KVFS ${kvfs_src})
