cmake_minimum_required(VERSION 3.24)
project(GenericQueue C)

set(CMAKE_C_STANDARD 11)

add_library(GenericQueue STATIC generic_queue.c generic_queue.h)

target_include_directories (GenericQueue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  enable_testing()
  add_subdirectory(tests)
endif()