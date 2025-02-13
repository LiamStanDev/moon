file(GLOB_RECURSE MOON_SRC ./*.cpp)

add_library(moon STATIC ${MOON_SRC})
target_include_directories(moon PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_compile_options(
    moon
    PRIVATE
        $<$<CONFIG:Debug>:${DEBUG_COMPILE_OPTIONS}>
        $<$<CONFIG:Release>:${RELEASE_COMPILE_OPTIONS}>
)
