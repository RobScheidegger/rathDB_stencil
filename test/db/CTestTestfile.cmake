# CMake generated Testfile for 
# Source directory: /home/robert/classes/csci1951l/rathDB_stencil/test/db
# Build directory: /home/robert/classes/csci1951l/rathDB_stencil/test/db
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Database.GetPutBasic "/home/robert/classes/csci1951l/rathDB_stencil/test/db/test_db" "--gtest_filter=Database.GetPutBasic")
set_tests_properties(Database.GetPutBasic PROPERTIES  _BACKTRACE_TRIPLES "/snap/cmake/888/share/cmake-3.20/Modules/GoogleTest.cmake;390;add_test;/home/robert/classes/csci1951l/rathDB_stencil/test/db/CMakeLists.txt;13;gtest_add_tests;/home/robert/classes/csci1951l/rathDB_stencil/test/db/CMakeLists.txt;0;")
add_test(Database.DeleteBasic "/home/robert/classes/csci1951l/rathDB_stencil/test/db/test_db" "--gtest_filter=Database.DeleteBasic")
set_tests_properties(Database.DeleteBasic PROPERTIES  _BACKTRACE_TRIPLES "/snap/cmake/888/share/cmake-3.20/Modules/GoogleTest.cmake;390;add_test;/home/robert/classes/csci1951l/rathDB_stencil/test/db/CMakeLists.txt;13;gtest_add_tests;/home/robert/classes/csci1951l/rathDB_stencil/test/db/CMakeLists.txt;0;")
add_test(Database.BatchGetPutBasic "/home/robert/classes/csci1951l/rathDB_stencil/test/db/test_db" "--gtest_filter=Database.BatchGetPutBasic")
set_tests_properties(Database.BatchGetPutBasic PROPERTIES  _BACKTRACE_TRIPLES "/snap/cmake/888/share/cmake-3.20/Modules/GoogleTest.cmake;390;add_test;/home/robert/classes/csci1951l/rathDB_stencil/test/db/CMakeLists.txt;13;gtest_add_tests;/home/robert/classes/csci1951l/rathDB_stencil/test/db/CMakeLists.txt;0;")
add_test(Database.BatchGetPutWithDelete "/home/robert/classes/csci1951l/rathDB_stencil/test/db/test_db" "--gtest_filter=Database.BatchGetPutWithDelete")
set_tests_properties(Database.BatchGetPutWithDelete PROPERTIES  _BACKTRACE_TRIPLES "/snap/cmake/888/share/cmake-3.20/Modules/GoogleTest.cmake;390;add_test;/home/robert/classes/csci1951l/rathDB_stencil/test/db/CMakeLists.txt;13;gtest_add_tests;/home/robert/classes/csci1951l/rathDB_stencil/test/db/CMakeLists.txt;0;")
