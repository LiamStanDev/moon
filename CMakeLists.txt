cmake_minimum_required(VERSION 3.20)

project(
    moon
    LANGUAGES CXX
    VERSION 0.1.0
    DESCRIPTION "Open-source modern c++ libraries"
    HOMEPAGE_URL "https://github.com/LiamStanDev/moon"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
    message(
        FATAL_ERROR
        "In-source builds are not allowed. Use 'cmake -B build' to specify a build directory."
    )
endif()

option(MOON_TEST "Open test suit" ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Project: ${PROJECT_NAME} (v${PROJECT_VERSION})")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} (${CMAKE_CXX_COMPILER})")
message(STATUS "C++ standard: C++${CMAKE_CXX_STANDARD}")

set(DEBUG_COMPILE_OPTIONS
    "-O0"
    "-g"
    "-DDEBUG"
    "-Wall"
    "-Wextra"
    "-Werror=uninitialized"
    "-Werror=return-type"
    "-Wconversion"
    "-Wsign-compare"
    "-Werror=unused-result"
    "-Werror=suggest-override"
    "-Wzero-as-null-pointer-constant"
    "-Wold-style-cast"
    "-Wnon-virtual-dtor"
)
set(RELEASE_COMPILE_OPTIONS "-O3" "-w" "-DNDEBUG")

add_subdirectory(src)

if(MOON_TEST)
    add_subdirectory(tests)
endif()
