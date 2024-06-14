add_executable(timeUnitTests
    libcsc/time.cpp
)

target_link_libraries(
    timeUnitTests
    PRIVATE
    GTest::gtest_main
    mytime
)

include(GoogleTest)
gtest_discover_tests(timeUnitTests)