include(FetchContent)

# Download google-test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY "https://github.com/google/googletest"
    GIT_TAG "6910c9d9165801d8827d628cb72eb7ea9dd538c5"
)
FetchContent_MakeAvailable(googletest)

# Test executables
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(test_runner ${TEST_SOURCES})

target_link_libraries(test_runner PRIVATE GTest::gtest_main nix)
include(GoogleTest)
gtest_discover_tests(test_runner)
