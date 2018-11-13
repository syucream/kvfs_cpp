cmake_minimum_required(VERSION 3.10)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")

project(kvfs)

set(kvfs_src
        src/fuse/kvfs.cpp
        src/drivers/leveldb.cpp
        )

if (APPLE)
    set(fuse_lib osxfuse)
    set(additional_includes /usr/local/include/osxfuse/fuse)
else ()
    set(fuse_lib fuse)
endif ()

set(kvfs_libs
        ${fuse_lib}
        leveldb
        )

add_executable(kvfs ${kvfs_src})
set_target_properties(kvfs PROPERTIES COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=29")
include_directories(${additional_includes})
target_link_libraries(kvfs ${kvfs_libs})