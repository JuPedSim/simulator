pybind11_add_module(jpscore
    jpscore_binding.cpp

    simulation_binding.hpp
    simulation_binding.cpp

    logging_binding.hpp
    logging_binding.cpp

    geometry/world_builder_binding.hpp
    geometry/world_builder_binding.cpp
    geometry/length_unit_binding.hpp
    geometry/length_unit_binding.cpp
)

target_link_libraries(jpscore
    PRIVATE
        core
)
