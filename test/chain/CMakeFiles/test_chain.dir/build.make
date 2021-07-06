# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/cmake/888/bin/cmake

# The command to remove a file.
RM = /snap/cmake/888/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/robert/classes/csci1951l/rathDB_stencil

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robert/classes/csci1951l/rathDB_stencil

# Include any dependencies generated for this target.
include test/chain/CMakeFiles/test_chain.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/chain/CMakeFiles/test_chain.dir/compiler_depend.make

# Include the progress variables for this target.
include test/chain/CMakeFiles/test_chain.dir/progress.make

# Include the compile flags for this target's objects.
include test/chain/CMakeFiles/test_chain.dir/flags.make

test/chain/CMakeFiles/test_chain.dir/main.cpp.o: test/chain/CMakeFiles/test_chain.dir/flags.make
test/chain/CMakeFiles/test_chain.dir/main.cpp.o: test/chain/main.cpp
test/chain/CMakeFiles/test_chain.dir/main.cpp.o: test/chain/CMakeFiles/test_chain.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/chain/CMakeFiles/test_chain.dir/main.cpp.o"
	cd /home/robert/classes/csci1951l/rathDB_stencil/test/chain && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/chain/CMakeFiles/test_chain.dir/main.cpp.o -MF CMakeFiles/test_chain.dir/main.cpp.o.d -o CMakeFiles/test_chain.dir/main.cpp.o -c /home/robert/classes/csci1951l/rathDB_stencil/test/chain/main.cpp

test/chain/CMakeFiles/test_chain.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_chain.dir/main.cpp.i"
	cd /home/robert/classes/csci1951l/rathDB_stencil/test/chain && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/classes/csci1951l/rathDB_stencil/test/chain/main.cpp > CMakeFiles/test_chain.dir/main.cpp.i

test/chain/CMakeFiles/test_chain.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_chain.dir/main.cpp.s"
	cd /home/robert/classes/csci1951l/rathDB_stencil/test/chain && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/classes/csci1951l/rathDB_stencil/test/chain/main.cpp -o CMakeFiles/test_chain.dir/main.cpp.s

# Object files for target test_chain
test_chain_OBJECTS = \
"CMakeFiles/test_chain.dir/main.cpp.o"

# External object files for target test_chain
test_chain_EXTERNAL_OBJECTS =

test/chain/test_chain: test/chain/CMakeFiles/test_chain.dir/main.cpp.o
test/chain/test_chain: test/chain/CMakeFiles/test_chain.dir/build.make
test/chain/test_chain: core/librathDB.a
test/chain/test_chain: lib/libgtest.a
test/chain/test_chain: core/libdb.a
test/chain/test_chain: core/libprimitives.a
test/chain/test_chain: core/libproto.a
test/chain/test_chain: /usr/local/lib/libprotobuf.so
test/chain/test_chain: core/libcrypto.a
test/chain/test_chain: test/chain/CMakeFiles/test_chain.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_chain"
	cd /home/robert/classes/csci1951l/rathDB_stencil/test/chain && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_chain.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/chain/CMakeFiles/test_chain.dir/build: test/chain/test_chain
.PHONY : test/chain/CMakeFiles/test_chain.dir/build

test/chain/CMakeFiles/test_chain.dir/clean:
	cd /home/robert/classes/csci1951l/rathDB_stencil/test/chain && $(CMAKE_COMMAND) -P CMakeFiles/test_chain.dir/cmake_clean.cmake
.PHONY : test/chain/CMakeFiles/test_chain.dir/clean

test/chain/CMakeFiles/test_chain.dir/depend:
	cd /home/robert/classes/csci1951l/rathDB_stencil && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robert/classes/csci1951l/rathDB_stencil /home/robert/classes/csci1951l/rathDB_stencil/test/chain /home/robert/classes/csci1951l/rathDB_stencil /home/robert/classes/csci1951l/rathDB_stencil/test/chain /home/robert/classes/csci1951l/rathDB_stencil/test/chain/CMakeFiles/test_chain.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/chain/CMakeFiles/test_chain.dir/depend

