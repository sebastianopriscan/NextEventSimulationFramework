cmake_minimum_required(VERSION 3.24)
project(NextEventSimulationSkeleton C)

set(CMAKE_C_STANDARD 11)

add_library(NextEventSimulationSkeleton simulation/simulation.c events/event.c event_queues/event_queue.c)