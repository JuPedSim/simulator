add_library(core
    log.cpp
    log.hpp
    simulation.cpp
    simulation.hpp

    util/identifiable.hpp

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
