cmake_minimum_required(VERSION 3.24)
project(NextEventSimulationSkeleton C)

include(CTest)

include_directories(..)

set(CMAKE_C_STANDARD 11)

add_executable(TestSimulation test_simulation.c)
target_link_libraries(TestSimulation NextEventSimulationFramework)
add_test(NAME TestSimulation
        COMMAND TestSimulation)