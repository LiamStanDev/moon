# StaticAnalysis.cmake - Enable static analysis tools

# clang-tidy
find_program(CLANG_TIDY_PATH clang-tidy)
if(NOT CLANG_TIDY_PATH)
    message(WARNING "clang-tidy not found. Disabling static analysis.")
    return()
endif()

# Configure clang-tidy
set(CMAKE_CXX_CLANG_TIDY
    ${CLANG_TIDY_PATH}
    -checks=clang-analyzer-*,modernize-*,performance-*,readability-*,bugprone-*
    -extra-arg=-std=c++${CMAKE_CXX_STANDARD}
    -warnings-as-errors=*
    -header-filter=.*
    -format-style=file
)

message(STATUS "Enabled clang-tidy for static analysis")

# cppcheck
find_program(CPPCHECK_PATH cppcheck)
if(CPPCHECK_PATH)
    set(CMAKE_CXX_CPPCHECK
        ${CPPCHECK_PATH}
        --enable=all
        --suppress=missingIncludeSystem
        --inline-suppr
        --std=c++${CMAKE_CXX_STANDARD}
    )
    message(STATUS "Enabled cppcheck for static analysis")
endif()
