# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ryo/repos/kvfs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ryo/repos/kvfs

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/ryo/repos/kvfs/CMakeFiles /Users/ryo/repos/kvfs/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/ryo/repos/kvfs/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named kvfs

# Build rule for target.
kvfs: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 kvfs
.PHONY : kvfs

# fast build rule for target.
kvfs/fast:
	$(MAKE) -f CMakeFiles/kvfs.dir/build.make CMakeFiles/kvfs.dir/build
.PHONY : kvfs/fast

src/drivers/leveldb.o: src/drivers/leveldb.cpp.o

.PHONY : src/drivers/leveldb.o

# target to build an object file
src/drivers/leveldb.cpp.o:
	$(MAKE) -f CMakeFiles/kvfs.dir/build.make CMakeFiles/kvfs.dir/src/drivers/leveldb.cpp.o
.PHONY : src/drivers/leveldb.cpp.o

src/drivers/leveldb.i: src/drivers/leveldb.cpp.i

.PHONY : src/drivers/leveldb.i

# target to preprocess a source file
src/drivers/leveldb.cpp.i:
	$(MAKE) -f CMakeFiles/kvfs.dir/build.make CMakeFiles/kvfs.dir/src/drivers/leveldb.cpp.i
.PHONY : src/drivers/leveldb.cpp.i

src/drivers/leveldb.s: src/drivers/leveldb.cpp.s

.PHONY : src/drivers/leveldb.s

# target to generate assembly for a file
src/drivers/leveldb.cpp.s:
	$(MAKE) -f CMakeFiles/kvfs.dir/build.make CMakeFiles/kvfs.dir/src/drivers/leveldb.cpp.s
.PHONY : src/drivers/leveldb.cpp.s

src/fuse/kvfs.o: src/fuse/kvfs.cpp.o

.PHONY : src/fuse/kvfs.o

# target to build an object file
src/fuse/kvfs.cpp.o:
	$(MAKE) -f CMakeFiles/kvfs.dir/build.make CMakeFiles/kvfs.dir/src/fuse/kvfs.cpp.o
.PHONY : src/fuse/kvfs.cpp.o

src/fuse/kvfs.i: src/fuse/kvfs.cpp.i

.PHONY : src/fuse/kvfs.i

# target to preprocess a source file
src/fuse/kvfs.cpp.i:
	$(MAKE) -f CMakeFiles/kvfs.dir/build.make CMakeFiles/kvfs.dir/src/fuse/kvfs.cpp.i
.PHONY : src/fuse/kvfs.cpp.i

src/fuse/kvfs.s: src/fuse/kvfs.cpp.s

.PHONY : src/fuse/kvfs.s

# target to generate assembly for a file
src/fuse/kvfs.cpp.s:
	$(MAKE) -f CMakeFiles/kvfs.dir/build.make CMakeFiles/kvfs.dir/src/fuse/kvfs.cpp.s
.PHONY : src/fuse/kvfs.cpp.s

src/fuse/main.o: src/fuse/main.cpp.o

.PHONY : src/fuse/main.o

# target to build an object file
src/fuse/main.cpp.o:
	$(MAKE) -f CMakeFiles/kvfs.dir/build.make CMakeFiles/kvfs.dir/src/fuse/main.cpp.o
.PHONY : src/fuse/main.cpp.o

src/fuse/main.i: src/fuse/main.cpp.i

.PHONY : src/fuse/main.i

# target to preprocess a source file
src/fuse/main.cpp.i:
	$(MAKE) -f CMakeFiles/kvfs.dir/build.make CMakeFiles/kvfs.dir/src/fuse/main.cpp.i
.PHONY : src/fuse/main.cpp.i

src/fuse/main.s: src/fuse/main.cpp.s

.PHONY : src/fuse/main.s

# target to generate assembly for a file
src/fuse/main.cpp.s:
	$(MAKE) -f CMakeFiles/kvfs.dir/build.make CMakeFiles/kvfs.dir/src/fuse/main.cpp.s
.PHONY : src/fuse/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... kvfs"
	@echo "... src/drivers/leveldb.o"
	@echo "... src/drivers/leveldb.i"
	@echo "... src/drivers/leveldb.s"
	@echo "... src/fuse/kvfs.o"
	@echo "... src/fuse/kvfs.i"
	@echo "... src/fuse/kvfs.s"
	@echo "... src/fuse/main.o"
	@echo "... src/fuse/main.i"
	@echo "... src/fuse/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

