if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Enabling strict compiler warnings")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wdouble-promotion
        -Wformat=2
        -Wno-unused-parameter
        -Werror=uninitialized
        -Werror=return-type
        -Wsign-compare
        -Werror=unused-result
        -Werror=suggest-override
        -Wzero-as-null-pointer-constant
        -Wnon-virtual-dtor
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Enabling strict compiler warnings for MSVC")
    add_compile_options(
        /W4
        /WX
        /wd4201 # Suppress nonstandard extension used: nameless struct/union
        /wd4127 # Suppress conditional expression is constant
    )
else()
    message(WARNING "Compiler warnings not configured for this compiler.")
endif()
