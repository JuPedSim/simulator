pybind11_add_module(jpscore
    simulator_binding.cpp
)

target_link_libraries(jpscore
    PRIVATE
        core
)
