add_library(core
    simulation.cpp
    simulation.hpp
)

target_include_directories(core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(core
    PUBLIC fmt::fmt
)
