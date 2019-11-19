cmake_minimum_required(VERSION 3.9...3.15)
if (${CMAKE_VERSION} VERSION_LESS 3.15)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else ()
    cmake_policy(VERSION 3.15)
endif ()

project(
    c-examples
    VERSION 1.0.0
    LANGUAGES C
)

include(cmake/utilities.cmake)

set(BUILD_TYPE ${CMAKE_BUILD_TYPE})
string(TOLOWER ${BUILD_TYPE} BUILD_TYPE)

set(DIST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dist)
set(EXECUTABLE_OUTPUT_PATH ${DIST_DIR}/${BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH ${DIST_DIR}/${BUILD_TYPE}/lib)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(command-line-arguments)
add_subdirectory(http-hello-world-server)
add_subdirectory(memory-mapped-io)
add_subdirectory(parking-pthreads)
add_subdirectory(pthreads)
add_subdirectory(read-from-console)
add_subdirectory(signalfd-with-epoll)
add_subdirectory(tcp-echo-server-with-epoll)
add_subdirectory(write-to-console)
