include(FetchContent)

# Download google-test
FetchContent_Declare(
    googletest
    URL
        https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test executables
file(GLOB TEST_SOURCES *.cpp)
add_executable(test_runner ${TEST_SOURCES})

target_link_libraries(test_runner PRIVATE GTest::gtest_main moon)
include(GoogleTest)
gtest_discover_tests(test_runner)
