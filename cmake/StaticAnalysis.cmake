# StaticAnalysis.cmake - Enable static analysis tools

# clang-tidy
find_program(CLANG_TIDY_PATH clang-tidy)
if(NOT CLANG_TIDY_PATH)
    message(WARNING "clang-tidy not found. Disabling static analysis.")
    return()
endif()

# Configure clang-tidy
set(CMAKE_CXX_CLANG_TIDY
    "${CLANG_TIDY_PATH}"
    "-extra-arg=-std=c++${CMAKE_CXX_STANDARD}"
    "-config=${CMAKE_SOURCE_DIR}/.clang-tidy"
)

message(STATUS "Enabled clang-tidy for static analysis")

# cppcheck
find_program(CPPCHECK_PATH cppcheck)
if(NOT CPPCHECK_PATH)
    message(WARNING "cppcheck not found. Disabling static analysis.")
    return()
endif()
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
