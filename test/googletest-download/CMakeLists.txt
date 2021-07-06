cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           master
  SOURCE_DIR        "/home/robert/classes/csci1951l/rathDB_stencil/googletest-src"
  BINARY_DIR        "/home/robert/classes/csci1951l/rathDB_stencil/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
