add_executable(test-core
    test_simulation.cpp
    test_dependency_availability.cpp

    util/test_unique_id.cpp
    util/test_simulation_clock.cpp

    geometry/test_area.cpp
    geometry/test_coordinate.cpp
    geometry/test_helper.cpp
    geometry/test_level.cpp
    geometry/test_length_unit.cpp
    geometry/test_line_segment.cpp
    geometry/test_spatial_vector.cpp
    geometry/test_special_area.cpp

    math/test_int_pow.cpp

    neighborhood/test_grid_2d.cpp
    neighborhood/test_neighborhood_search.cpp
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

list(APPEND TEST_COMPILE_OPTIONS
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wall>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wextra>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wconversion>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wimplicit-fallthrough>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wsign-conversion>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-fdiagnostics-color=always>
        $<$<CXX_COMPILER_ID:Clang>:-Wno-self-assign-overloaded>
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<CXX_COMPILER_ID:MSVC>:/EHsc>
        -fPIC
        )

target_compile_options(test-core PRIVATE
    ${TEST_COMPILE_OPTIONS}
)
