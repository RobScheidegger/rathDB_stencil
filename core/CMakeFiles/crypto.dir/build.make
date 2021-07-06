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
include core/CMakeFiles/crypto.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include core/CMakeFiles/crypto.dir/compiler_depend.make

# Include the progress variables for this target.
include core/CMakeFiles/crypto.dir/progress.make

# Include the compile flags for this target's objects.
include core/CMakeFiles/crypto.dir/flags.make

core/CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.o: core/CMakeFiles/crypto.dir/flags.make
core/CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.o: core/src/crypto/rathcrypto.cpp
core/CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.o: core/CMakeFiles/crypto.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.o"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.o -MF CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.o.d -o CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.o -c /home/robert/classes/csci1951l/rathDB_stencil/core/src/crypto/rathcrypto.cpp

core/CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.i"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/classes/csci1951l/rathDB_stencil/core/src/crypto/rathcrypto.cpp > CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.i

core/CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.s"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/classes/csci1951l/rathDB_stencil/core/src/crypto/rathcrypto.cpp -o CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.s

# Object files for target crypto
crypto_OBJECTS = \
"CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.o"

# External object files for target crypto
crypto_EXTERNAL_OBJECTS =

core/libcrypto.a: core/CMakeFiles/crypto.dir/src/crypto/rathcrypto.cpp.o
core/libcrypto.a: core/CMakeFiles/crypto.dir/build.make
core/libcrypto.a: core/CMakeFiles/crypto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcrypto.a"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && $(CMAKE_COMMAND) -P CMakeFiles/crypto.dir/cmake_clean_target.cmake
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crypto.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
core/CMakeFiles/crypto.dir/build: core/libcrypto.a
.PHONY : core/CMakeFiles/crypto.dir/build

core/CMakeFiles/crypto.dir/clean:
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && $(CMAKE_COMMAND) -P CMakeFiles/crypto.dir/cmake_clean.cmake
.PHONY : core/CMakeFiles/crypto.dir/clean

core/CMakeFiles/crypto.dir/depend:
	cd /home/robert/classes/csci1951l/rathDB_stencil && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robert/classes/csci1951l/rathDB_stencil /home/robert/classes/csci1951l/rathDB_stencil/core /home/robert/classes/csci1951l/rathDB_stencil /home/robert/classes/csci1951l/rathDB_stencil/core /home/robert/classes/csci1951l/rathDB_stencil/core/CMakeFiles/crypto.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : core/CMakeFiles/crypto.dir/depend

