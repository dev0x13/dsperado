cmake_minimum_required(VERSION 3.8)
project(dsperado)

option(USE_FFTW "Use FFTW (needed by HilbertTransformer)" ON)
option(STATIC "Build static library" OFF)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

file(GLOB_RECURSE SOURCE_FILES
        src/FIR.cpp
        src/XCorr.cpp)

if (USE_FFTW MATCHES ON)
    list(APPEND SOURCE_FILES
            src/HilbertTransformer.cpp)
endif()

set(INCLUDE_DIR include/)

if (STATIC MATCHES ON)
    add_library(dsperado STATIC ${SOURCE_FILES})
else()
    add_library(dsperado SHARED ${SOURCE_FILES})
endif()

### FFTW

if (USE_FFTW MATCHES ON)
    add_library(fftw3 INTERFACE IMPORTED GLOBAL)

    set(fftw3_headers ${CMAKE_SOURCE_DIR}/lib/fftw3/api)
    if (STATIC MATCHES ON)
        set(fftw3_libs ${CMAKE_SOURCE_DIR}/lib/fftw3/.libs/libfftw3.a)
    else()
        set(fftw3_libs ${CMAKE_SOURCE_DIR}/lib/fftw3/build/libfftw3.so)
    endif()

    set_property(TARGET fftw3 PROPERTY
            INTERFACE_LINK_LIBRARIES
            ${fftw3_libs})
    set_property(TARGET fftw3 PROPERTY
            INTERFACE_INCLUDE_DIRECTORIES
            ${fftw3_headers})

    target_link_libraries(dsperado PUBLIC
            fftw3
            )
endif()

target_include_directories(dsperado PRIVATE
        ${INCLUDE_DIR})
