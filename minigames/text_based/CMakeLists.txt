cmake_minimum_required(VERSION 3.0)

project(game3)

add_library(CoreFunc core_functions.cpp)
find_package(Threads REQUIRED)

if(CMAKE_HOST_SYSTEM MATCHES Linux)
   set(CMAKE_CXX_COMPILER g++)
endif()

if(CMAKE_HOST_SYSTEM MATCHES Darwin)
   set(CMAKE_CXX_COMPILER g++)
endif()

if(CMAKE_SYSTEM MATCHES Windows)
   set(CMAKE_CXX_COMPILER i586-mingw32msvc-g++)
endif()
add_definitions(-std=c++14 -Wall -pthread)
add_executable(game game.cpp)

target_link_libraries(game CoreFunc)
target_link_libraries(game pthread)

if(CMAKE_HOST_SYSTEM MATCHES Windows)
   message(STATUS "Target system is Windows")
endif()

if(CMAKE_HOST_SYSTEM MATCHES Linux)
   message(STATUS "Build host runs Linux")
endif()

if(CMAKE_HOST_SYSTEM MATCHES Darwin)
   message(STATUS "Build host runs MacOS")
endif()
