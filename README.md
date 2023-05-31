# NextEventSimulationFramework

## Usage as a Git Submodule

1.  Execute the following commands to initialize and add the library to the project:

    ```bash
    git submodule init
    git submodule add https://github.com/SebastianOpriscan/NextEventSimulationFramework libs/NextEventSimulationFramework
    ```

2.  Create a `CMakeLists.txt` like the example below

    ```cmake
    cmake_minimum_required(VERSION 3.24)
    project(project_name C)

    set(CMAKE_C_STANDARD 11)

    find_package(Git QUIET)
    if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
        option(GIT_SUBMODULE "Check submodules during build" ON)
        if(GIT_SUBMODULE)
            message(STATUS "Submodule update")
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                            RESULT_VARIABLE GIT_SUBMOD_RESULT)
            if(NOT GIT_SUBMOD_RESULT EQUAL "0")
                message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
            endif()
        endif()
    endif()

    if(NOT EXISTS "${PROJECT_SOURCE_DIR}/libs/NextEventSimulationFramework/CMakeLists.txt")
        message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
    endif()

    add_subdirectory(libs/NextEventSimulationFramework)

    add_executable(project_name src/main.c)

    target_link_libraries(project_name PRIVATE NextEventSimulationFramework)
    ```

3.  The library can now be imported like this:

    ```c
    #include <simulation/simulation.h>
    #include <events/event.h>
    #include <event_queues/event_queue.h>
    ```
