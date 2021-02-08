add_executable(test-core
    test_simulation.cpp
    test_dependency_availability.cpp

    util/test_identifiable.cpp

    geometry/test_level.cpp
    geometry/test_length_unit.cpp

    math/test_int_pow.cpp
)

target_link_libraries(test-core
    PRIVATE
        core
        fmt::fmt
        GTest::gtest_main
        GTest::gtest
        GTest::gmock
)

gtest_discover_tests(test-core)


target_compile_options(test-core PRIVATE
    -fPIC
)
