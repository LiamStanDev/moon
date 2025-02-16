cmake_minimum_required(VERSION 3.25)

project(
    moon
    VERSION 0.1.0
    DESCRIPTION "Modern C++ project template"
    HOMEPAGE_URL "https://github.com/Liam/moon"
    LANGUAGES CXX
)

# Core configuration
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build directory guard
if(PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Use: cmake -B build")
endif()

# Project options
option(MOON_ENABLE_WARNING "Enable warnings" OFF)
option(MOON_BUILD_TESTS "Build test suite" ON)
option(MOON_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

message(STATUS "Project: ${PROJECT_NAME} (v${PROJECT_VERSION})")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} (${CMAKE_CXX_COMPILER})")
message(STATUS "C++ standard: C++${CMAKE_CXX_STANDARD}")

# Include CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Dependencies)

add_subdirectory(moon)
add_subdirectory(nix)

if(MOON_ENABLE_WARNING)
    include(CompilerWarnings)
endif()

if(MOON_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(MOON_ENABLE_CLANG_TIDY)
    include(StaticAnalysis)
endif()
