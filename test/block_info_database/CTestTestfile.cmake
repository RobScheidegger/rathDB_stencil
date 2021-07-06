# CMake generated Testfile for 
# Source directory: /home/robert/classes/csci1951l/rathDB_stencil/test/block_info_database
# Build directory: /home/robert/classes/csci1951l/rathDB_stencil/test/block_info_database
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(BlockRecord.Serializaiton "/home/robert/classes/csci1951l/rathDB_stencil/test/block_info_database/test_block_info_database" "--gtest_filter=BlockRecord.Serializaiton")
set_tests_properties(BlockRecord.Serializaiton PROPERTIES  _BACKTRACE_TRIPLES "/snap/cmake/888/share/cmake-3.20/Modules/GoogleTest.cmake;390;add_test;/home/robert/classes/csci1951l/rathDB_stencil/test/block_info_database/CMakeLists.txt;13;gtest_add_tests;/home/robert/classes/csci1951l/rathDB_stencil/test/block_info_database/CMakeLists.txt;0;")
add_test(UndoBlock.Serializaiton "/home/robert/classes/csci1951l/rathDB_stencil/test/block_info_database/test_block_info_database" "--gtest_filter=UndoBlock.Serializaiton")
set_tests_properties(UndoBlock.Serializaiton PROPERTIES  _BACKTRACE_TRIPLES "/snap/cmake/888/share/cmake-3.20/Modules/GoogleTest.cmake;390;add_test;/home/robert/classes/csci1951l/rathDB_stencil/test/block_info_database/CMakeLists.txt;13;gtest_add_tests;/home/robert/classes/csci1951l/rathDB_stencil/test/block_info_database/CMakeLists.txt;0;")
