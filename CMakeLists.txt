cmake_minimum_required(VERSION 3.24)
project(NextEventSimulationFramework C)

# include(GNUInstallDirs)

set(CMAKE_C_STANDARD 11)

# option(INSTALL_GLOBAL "Install library globally" OFF)

add_library(
  NextEventSimulationFramework
  STATIC
  simulation/simulation.c simulation/simulation.h
  events/event.c events/event.h
  event_queues/event_queue.c event_queues/event_queue.h
)

target_include_directories (NextEventSimulationFramework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# install(TARGETS NextEventSimulationFramework
#     EXPORT NextEventSimulationFrameworkTargets
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#     INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#     )

# install(FILES simulation/simulation.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# install(EXPORT NextEventSimulationFrameworkTargets
#     FILE NextEventSimulationFrameworkTargets.cmake
#     NAMESPACE NextEventSimulationFramework::
#     DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NextEventSimulationFramework
#     )
