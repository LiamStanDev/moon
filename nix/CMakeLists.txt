file(GLOB_RECURSE NIX_SRC CONFIGURE_DEPENDS *.cpp)

add_library(nix STATIC)
target_sources(nix PRIVATE ${NIX_SRC})
target_include_directories(nix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
