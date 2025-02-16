file(GLOB_RECURSE MOON_SRC CONFIGURE_DEPENDS src/*.cpp)

add_library(moon STATIC)
target_sources(moon PRIVATE ${MOON_SRC})
target_link_libraries(moon PRIVATE nix)
target_include_directories(moon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
