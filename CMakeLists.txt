cmake_minimum_required(VERSION 3.24)
project(NextEventSimulationSkeleton C)

include(GNUInstallDirs)

set(CMAKE_C_STANDARD 11)

option(INSTALL_GLOBAL "Install library globally" OFF)

add_library(NextEventSimulationFramework STATIC simulation/simulation.c events/event.c event_queues/event_queue.c)

install(TARGETS NextEventSimulationFramework
    EXPORT NextEventSimulationFrameworkTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

install(FILES simulation/simulation.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT NextEventSimulationFrameworkTargets
    FILE NextEventSimulationFrameworkTargets.cmake
    NAMESPACE NextEventSimulationFramework::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NextEventSimulationFramework
    )