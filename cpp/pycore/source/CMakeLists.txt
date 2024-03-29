pybind11_add_module(jpscore
    jpscore_binding.cpp

    simulation_binding.hpp
    simulation_binding.cpp

    logging_binding.hpp
    logging_binding.cpp

    agent/agent_binding.hpp
    agent/agent_binding.cpp

    geometry/area_binding.hpp
    geometry/area_binding.cpp
    geometry/coordinate_binding.hpp
    geometry/coordinate_binding.cpp
    geometry/length_unit_binding.hpp
    geometry/length_unit_binding.cpp
    geometry/level_binding.hpp
    geometry/level_binding.cpp
    geometry/level_storage_binding.hpp
    geometry/level_storage_binding.cpp
    geometry/line_segment_binding.hpp
    geometry/line_segment_binding.cpp
    geometry/spatial_vector_binding.hpp
    geometry/spatial_vector_binding.cpp
    geometry/special_area_binding.hpp
    geometry/special_area_binding.cpp
    geometry/world_binding.hpp
    geometry/world_binding.cpp

    util/jpsexception_binding.hpp
    util/jpsexception_binding.cpp
    util/simulation_clock_binding.hpp
    util/simulation_clock_binding.cpp
    util/unique_id_binding.hpp
    util/unique_id_binding.cpp
)

target_link_libraries(jpscore
    PRIVATE
        core
)

target_compile_options(jpscore PRIVATE
    ${COMMON_COMPILE_OPTIONS}
)

