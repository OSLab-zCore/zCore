# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /home/yuzc/miniconda3/bin/cmake

# The command to remove a file.
RM = /home/yuzc/miniconda3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /data/private/yuzc/OS/riscv64-linux-musl-cross/ucore

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /data/private/yuzc/OS/riscv64-linux-musl-cross/ucore

# Include any dependencies generated for this target.
include CMakeFiles/test_ls.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_ls.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_ls.dir/flags.make

CMakeFiles/test_ls.dir/src/test_ls.c.o: CMakeFiles/test_ls.dir/flags.make
CMakeFiles/test_ls.dir/src/test_ls.c.o: src/test_ls.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/private/yuzc/OS/riscv64-linux-musl-cross/ucore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/test_ls.dir/src/test_ls.c.o"
	riscv64-linux-musl-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test_ls.dir/src/test_ls.c.o   -c /data/private/yuzc/OS/riscv64-linux-musl-cross/ucore/src/test_ls.c

CMakeFiles/test_ls.dir/src/test_ls.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_ls.dir/src/test_ls.c.i"
	riscv64-linux-musl-gcc  $(C_DEFINES) $(C_FLAGS) -E /data/private/yuzc/OS/riscv64-linux-musl-cross/ucore/src/test_ls.c > CMakeFiles/test_ls.dir/src/test_ls.c.i

CMakeFiles/test_ls.dir/src/test_ls.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_ls.dir/src/test_ls.c.s"
	riscv64-linux-musl-gcc  $(C_DEFINES) $(C_FLAGS) -S /data/private/yuzc/OS/riscv64-linux-musl-cross/ucore/src/test_ls.c -o CMakeFiles/test_ls.dir/src/test_ls.c.s

CMakeFiles/test_ls.dir/src/test_ls.c.o.requires:

.PHONY : CMakeFiles/test_ls.dir/src/test_ls.c.o.requires

CMakeFiles/test_ls.dir/src/test_ls.c.o.provides: CMakeFiles/test_ls.dir/src/test_ls.c.o.requires
	$(MAKE) -f CMakeFiles/test_ls.dir/build.make CMakeFiles/test_ls.dir/src/test_ls.c.o.provides.build
.PHONY : CMakeFiles/test_ls.dir/src/test_ls.c.o.provides

CMakeFiles/test_ls.dir/src/test_ls.c.o.provides.build: CMakeFiles/test_ls.dir/src/test_ls.c.o


# Object files for target test_ls
test_ls_OBJECTS = \
"CMakeFiles/test_ls.dir/src/test_ls.c.o"

# External object files for target test_ls
test_ls_EXTERNAL_OBJECTS =

riscv64/test_ls: CMakeFiles/test_ls.dir/src/test_ls.c.o
riscv64/test_ls: CMakeFiles/test_ls.dir/build.make
riscv64/test_ls: libulib.a
riscv64/test_ls: CMakeFiles/test_ls.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/data/private/yuzc/OS/riscv64-linux-musl-cross/ucore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable riscv64/test_ls"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_ls.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_ls.dir/build: riscv64/test_ls

.PHONY : CMakeFiles/test_ls.dir/build

CMakeFiles/test_ls.dir/requires: CMakeFiles/test_ls.dir/src/test_ls.c.o.requires

.PHONY : CMakeFiles/test_ls.dir/requires

CMakeFiles/test_ls.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_ls.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_ls.dir/clean

CMakeFiles/test_ls.dir/depend:
	cd /data/private/yuzc/OS/riscv64-linux-musl-cross/ucore && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/private/yuzc/OS/riscv64-linux-musl-cross/ucore /data/private/yuzc/OS/riscv64-linux-musl-cross/ucore /data/private/yuzc/OS/riscv64-linux-musl-cross/ucore /data/private/yuzc/OS/riscv64-linux-musl-cross/ucore /data/private/yuzc/OS/riscv64-linux-musl-cross/ucore/CMakeFiles/test_ls.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_ls.dir/depend

