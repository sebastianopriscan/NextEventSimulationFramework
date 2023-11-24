cmake_minimum_required(VERSION 3.24)
project(NextEventSimulationFramework C)

set(CMAKE_C_STANDARD 11)

add_library(
  NextEventSimulationFramework
  STATIC
  simulation/simulation.c simulation/simulation.h
  events/event.c events/event.h
  event_queues/event_queue.c event_queues/event_queue.h
)

target_compile_definitions(NextEventSimulationFramework PRIVATE COMPILATION_H)

target_include_directories (NextEventSimulationFramework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories (NextEventSimulationFramework PUBLIC libs/RandomVariates)
target_include_directories (NextEventSimulationFramework PUBLIC libs/GenericQueue)

add_subdirectory(libs/RandomVariates)
add_subdirectory(libs/GenericQueue)

target_link_libraries(NextEventSimulationFramework PRIVATE RandomVariates m)
target_link_libraries(NextEventSimulationFramework PRIVATE GenericQueue)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  enable_testing()
  add_subdirectory(tests)
endif()
