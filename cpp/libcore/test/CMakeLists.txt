add_executable(test-core
    test_simulation.cpp
)

target_link_libraries(test-core
    PRIVATE
        core
        GTest::gtest_main
        GTest::gtest
        GTest::gmock
)

gtest_discover_tests(test-core)
