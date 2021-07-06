# CMake generated Testfile for 
# Source directory: /home/robert/classes/csci1951l/rathDB_stencil/test/coin_database
# Build directory: /home/robert/classes/csci1951l/rathDB_stencil/test/coin_database
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(CoinLocator.Serialize "/home/robert/classes/csci1951l/rathDB_stencil/test/coin_database/test_coin_database" "--gtest_filter=CoinLocator.Serialize")
set_tests_properties(CoinLocator.Serialize PROPERTIES  _BACKTRACE_TRIPLES "/snap/cmake/888/share/cmake-3.20/Modules/GoogleTest.cmake;390;add_test;/home/robert/classes/csci1951l/rathDB_stencil/test/coin_database/CMakeLists.txt;13;gtest_add_tests;/home/robert/classes/csci1951l/rathDB_stencil/test/coin_database/CMakeLists.txt;0;")
add_test(CoinRecord.Serialize "/home/robert/classes/csci1951l/rathDB_stencil/test/coin_database/test_coin_database" "--gtest_filter=CoinRecord.Serialize")
set_tests_properties(CoinRecord.Serialize PROPERTIES  _BACKTRACE_TRIPLES "/snap/cmake/888/share/cmake-3.20/Modules/GoogleTest.cmake;390;add_test;/home/robert/classes/csci1951l/rathDB_stencil/test/coin_database/CMakeLists.txt;13;gtest_add_tests;/home/robert/classes/csci1951l/rathDB_stencil/test/coin_database/CMakeLists.txt;0;")
