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
include core/CMakeFiles/rathDB.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include core/CMakeFiles/rathDB.dir/compiler_depend.make

# Include the progress variables for this target.
include core/CMakeFiles/rathDB.dir/progress.make

# Include the compile flags for this target's objects.
include core/CMakeFiles/rathDB.dir/flags.make

core/CMakeFiles/rathDB.dir/src/chain/chain.cpp.o: core/CMakeFiles/rathDB.dir/flags.make
core/CMakeFiles/rathDB.dir/src/chain/chain.cpp.o: core/src/chain/chain.cpp
core/CMakeFiles/rathDB.dir/src/chain/chain.cpp.o: core/CMakeFiles/rathDB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/CMakeFiles/rathDB.dir/src/chain/chain.cpp.o"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/rathDB.dir/src/chain/chain.cpp.o -MF CMakeFiles/rathDB.dir/src/chain/chain.cpp.o.d -o CMakeFiles/rathDB.dir/src/chain/chain.cpp.o -c /home/robert/classes/csci1951l/rathDB_stencil/core/src/chain/chain.cpp

core/CMakeFiles/rathDB.dir/src/chain/chain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathDB.dir/src/chain/chain.cpp.i"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/classes/csci1951l/rathDB_stencil/core/src/chain/chain.cpp > CMakeFiles/rathDB.dir/src/chain/chain.cpp.i

core/CMakeFiles/rathDB.dir/src/chain/chain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathDB.dir/src/chain/chain.cpp.s"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/classes/csci1951l/rathDB_stencil/core/src/chain/chain.cpp -o CMakeFiles/rathDB.dir/src/chain/chain.cpp.s

core/CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.o: core/CMakeFiles/rathDB.dir/flags.make
core/CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.o: core/src/chain_writer/chain_writer.cpp
core/CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.o: core/CMakeFiles/rathDB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object core/CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.o"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.o -MF CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.o.d -o CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.o -c /home/robert/classes/csci1951l/rathDB_stencil/core/src/chain_writer/chain_writer.cpp

core/CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.i"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/classes/csci1951l/rathDB_stencil/core/src/chain_writer/chain_writer.cpp > CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.i

core/CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.s"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/classes/csci1951l/rathDB_stencil/core/src/chain_writer/chain_writer.cpp -o CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.s

core/CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.o: core/CMakeFiles/rathDB.dir/flags.make
core/CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.o: core/src/chain_writer/file_info.cpp
core/CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.o: core/CMakeFiles/rathDB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object core/CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.o"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.o -MF CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.o.d -o CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.o -c /home/robert/classes/csci1951l/rathDB_stencil/core/src/chain_writer/file_info.cpp

core/CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.i"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/classes/csci1951l/rathDB_stencil/core/src/chain_writer/file_info.cpp > CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.i

core/CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.s"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/classes/csci1951l/rathDB_stencil/core/src/chain_writer/file_info.cpp -o CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.s

core/CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.o: core/CMakeFiles/rathDB.dir/flags.make
core/CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.o: core/src/chain_writer/undo_block.cpp
core/CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.o: core/CMakeFiles/rathDB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object core/CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.o"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.o -MF CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.o.d -o CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.o -c /home/robert/classes/csci1951l/rathDB_stencil/core/src/chain_writer/undo_block.cpp

core/CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.i"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/classes/csci1951l/rathDB_stencil/core/src/chain_writer/undo_block.cpp > CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.i

core/CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.s"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/classes/csci1951l/rathDB_stencil/core/src/chain_writer/undo_block.cpp -o CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.s

core/CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.o: core/CMakeFiles/rathDB.dir/flags.make
core/CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.o: core/src/coin_database/coin.cpp
core/CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.o: core/CMakeFiles/rathDB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object core/CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.o"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.o -MF CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.o.d -o CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.o -c /home/robert/classes/csci1951l/rathDB_stencil/core/src/coin_database/coin.cpp

core/CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.i"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/classes/csci1951l/rathDB_stencil/core/src/coin_database/coin.cpp > CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.i

core/CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.s"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/classes/csci1951l/rathDB_stencil/core/src/coin_database/coin.cpp -o CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.s

core/CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.o: core/CMakeFiles/rathDB.dir/flags.make
core/CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.o: core/src/coin_database/coin_database.cpp
core/CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.o: core/CMakeFiles/rathDB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object core/CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.o"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.o -MF CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.o.d -o CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.o -c /home/robert/classes/csci1951l/rathDB_stencil/core/src/coin_database/coin_database.cpp

core/CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.i"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/classes/csci1951l/rathDB_stencil/core/src/coin_database/coin_database.cpp > CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.i

core/CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.s"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/classes/csci1951l/rathDB_stencil/core/src/coin_database/coin_database.cpp -o CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.s

core/CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.o: core/CMakeFiles/rathDB.dir/flags.make
core/CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.o: core/src/coin_database/coin_record.cpp
core/CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.o: core/CMakeFiles/rathDB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object core/CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.o"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.o -MF CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.o.d -o CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.o -c /home/robert/classes/csci1951l/rathDB_stencil/core/src/coin_database/coin_record.cpp

core/CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.i"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/classes/csci1951l/rathDB_stencil/core/src/coin_database/coin_record.cpp > CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.i

core/CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.s"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/classes/csci1951l/rathDB_stencil/core/src/coin_database/coin_record.cpp -o CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.s

core/CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.o: core/CMakeFiles/rathDB.dir/flags.make
core/CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.o: core/src/coin_database/undo_coin_record.cpp
core/CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.o: core/CMakeFiles/rathDB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object core/CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.o"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.o -MF CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.o.d -o CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.o -c /home/robert/classes/csci1951l/rathDB_stencil/core/src/coin_database/undo_coin_record.cpp

core/CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.i"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/classes/csci1951l/rathDB_stencil/core/src/coin_database/undo_coin_record.cpp > CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.i

core/CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.s"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/classes/csci1951l/rathDB_stencil/core/src/coin_database/undo_coin_record.cpp -o CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.s

core/CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.o: core/CMakeFiles/rathDB.dir/flags.make
core/CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.o: core/src/block_info_database/block_info_database.cpp
core/CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.o: core/CMakeFiles/rathDB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object core/CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.o"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.o -MF CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.o.d -o CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.o -c /home/robert/classes/csci1951l/rathDB_stencil/core/src/block_info_database/block_info_database.cpp

core/CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.i"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/classes/csci1951l/rathDB_stencil/core/src/block_info_database/block_info_database.cpp > CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.i

core/CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.s"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/classes/csci1951l/rathDB_stencil/core/src/block_info_database/block_info_database.cpp -o CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.s

core/CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.o: core/CMakeFiles/rathDB.dir/flags.make
core/CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.o: core/src/block_info_database/block_record.cpp
core/CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.o: core/CMakeFiles/rathDB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object core/CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.o"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.o -MF CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.o.d -o CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.o -c /home/robert/classes/csci1951l/rathDB_stencil/core/src/block_info_database/block_record.cpp

core/CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.i"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robert/classes/csci1951l/rathDB_stencil/core/src/block_info_database/block_record.cpp > CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.i

core/CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.s"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robert/classes/csci1951l/rathDB_stencil/core/src/block_info_database/block_record.cpp -o CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.s

# Object files for target rathDB
rathDB_OBJECTS = \
"CMakeFiles/rathDB.dir/src/chain/chain.cpp.o" \
"CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.o" \
"CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.o" \
"CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.o" \
"CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.o" \
"CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.o" \
"CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.o" \
"CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.o" \
"CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.o" \
"CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.o"

# External object files for target rathDB
rathDB_EXTERNAL_OBJECTS =

core/librathDB.a: core/CMakeFiles/rathDB.dir/src/chain/chain.cpp.o
core/librathDB.a: core/CMakeFiles/rathDB.dir/src/chain_writer/chain_writer.cpp.o
core/librathDB.a: core/CMakeFiles/rathDB.dir/src/chain_writer/file_info.cpp.o
core/librathDB.a: core/CMakeFiles/rathDB.dir/src/chain_writer/undo_block.cpp.o
core/librathDB.a: core/CMakeFiles/rathDB.dir/src/coin_database/coin.cpp.o
core/librathDB.a: core/CMakeFiles/rathDB.dir/src/coin_database/coin_database.cpp.o
core/librathDB.a: core/CMakeFiles/rathDB.dir/src/coin_database/coin_record.cpp.o
core/librathDB.a: core/CMakeFiles/rathDB.dir/src/coin_database/undo_coin_record.cpp.o
core/librathDB.a: core/CMakeFiles/rathDB.dir/src/block_info_database/block_info_database.cpp.o
core/librathDB.a: core/CMakeFiles/rathDB.dir/src/block_info_database/block_record.cpp.o
core/librathDB.a: core/CMakeFiles/rathDB.dir/build.make
core/librathDB.a: core/CMakeFiles/rathDB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/robert/classes/csci1951l/rathDB_stencil/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX static library librathDB.a"
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && $(CMAKE_COMMAND) -P CMakeFiles/rathDB.dir/cmake_clean_target.cmake
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rathDB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
core/CMakeFiles/rathDB.dir/build: core/librathDB.a
.PHONY : core/CMakeFiles/rathDB.dir/build

core/CMakeFiles/rathDB.dir/clean:
	cd /home/robert/classes/csci1951l/rathDB_stencil/core && $(CMAKE_COMMAND) -P CMakeFiles/rathDB.dir/cmake_clean.cmake
.PHONY : core/CMakeFiles/rathDB.dir/clean

core/CMakeFiles/rathDB.dir/depend:
	cd /home/robert/classes/csci1951l/rathDB_stencil && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robert/classes/csci1951l/rathDB_stencil /home/robert/classes/csci1951l/rathDB_stencil/core /home/robert/classes/csci1951l/rathDB_stencil /home/robert/classes/csci1951l/rathDB_stencil/core /home/robert/classes/csci1951l/rathDB_stencil/core/CMakeFiles/rathDB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : core/CMakeFiles/rathDB.dir/depend

