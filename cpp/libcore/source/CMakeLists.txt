add_library(core
    log.cpp
    log.hpp
    simulation.cpp
    simulation.hpp

    agent/agent.hpp
    agent/pedestrian.hpp

    geometry/area.cpp
    geometry/area.hpp
    geometry/coordinate.cpp
    geometry/coordinate.hpp
    geometry/helper/polygon_helper.cpp
    geometry/helper/polygon_helper.hpp
    geometry/length_unit.hpp
    geometry/level.cpp
    geometry/level.hpp
    geometry/level_storage.cpp
    geometry/level_storage.hpp
    geometry/line_segment.cpp
    geometry/line_segment.hpp
    geometry/spatial_vector.cpp
    geometry/spatial_vector.hpp
    geometry/special_area.cpp
    geometry/special_area.hpp
    geometry/world.cpp
    geometry/world.hpp

    math/int_pow.hpp

    neighborhood/grid_2d.hpp
    neighborhood/neighborhood_search.cpp
    neighborhood/neighborhood_search.hpp

    util/unique_id.hpp
    util/jpsexception.hpp
    util/simulation_clock.hpp

    operational/operational.hpp
    operational/result.hpp

    strategic/result.hpp
    strategic/strategic.hpp

    tactical/result.hpp
    tactical/tactical.hpp
)

target_include_directories(core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(core
    PUBLIC fmt::fmt
)

target_compile_options(core PRIVATE
    ${COMMON_COMPILE_OPTIONS}
)
