cmake_minimum_required(VERSION 3.8)
project(dsperado_example)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

set(INCLUDE_DIR include/)

add_executable(dsperado_example ${SOURCE_FILES})

target_include_directories(dsperado_example PRIVATE ${INCLUDE_DIR})
