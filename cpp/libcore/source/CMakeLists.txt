add_library(core
    log.cpp
    log.hpp
    simulation.cpp
    simulation.hpp

    util/identifiable.hpp

    geometry/area.cpp
    geometry/area.hpp
    geometry/coordinate.cpp
    geometry/coordinate.hpp
    geometry/length_unit.hpp
    geometry/level.cpp
    geometry/level.hpp
    geometry/line_segment.cpp
    geometry/line_segment.hpp
    geometry/spatial_vector.cpp
    geometry/spatial_vector.hpp
    geometry/special_area.cpp
    geometry/special_area.hpp

    math/int_pow.hpp
)

target_include_directories(core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(core
    PUBLIC fmt::fmt
)

target_compile_options(core PRIVATE
    -fPIC
)
