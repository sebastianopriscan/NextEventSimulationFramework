cmake_minimum_required(VERSION 3.24)
project(GenericQueue C)

include(CTest)

include_directories(..)

set(CMAKE_C_STANDARD 11)

add_executable(TestGenericQueue test_generic_queue.c)
target_link_libraries(TestGenericQueue GenericQueue)
add_test(NAME TestGenericQueue
        COMMAND TestGenericQueue)