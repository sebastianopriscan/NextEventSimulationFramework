cmake_minimum_required(VERSION 3.24)
project(NextEventSimulationSkeleton C)

include(CTest)

include_directories(..)

set(CMAKE_C_STANDARD 11)

add_executable(TestSimulation test_simulation.c)
target_link_libraries(TestSimulation NextEventSimulationFramework)
add_test(NAME TestSimulation
        COMMAND TestSimulation)

add_executable(TestSimMetadata test_simulation_metadata.c)
target_link_libraries(TestSimMetadata NextEventSimulationFramework)
add_test(NAME TestSimMetadata
        COMMAND TestSimMetadata)

add_executable(TestSimMM1 test_simulation_mm1.c)
target_link_libraries(TestSimMM1 NextEventSimulationFramework RandomVariates m)
add_test(NAME TestSimMM1
        COMMAND TestSimMM1)

add_executable(TestEventRemoval test_event_removal.c)
target_link_libraries(TestEventRemoval NextEventSimulationFramework RandomVariates m)
add_test(NAME TestEventRemoval 
        COMMAND TestEventRemoval)