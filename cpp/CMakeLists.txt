cmake_minimum_required(VERSION 3.18)
project(simulator CXX)

################################################################################
# Project setup
################################################################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(helper_functions)
check_prefix_path()
enforce_build_type_is_set()
add_clang_tidy_support_option()

################################################################################
# Dependencies
################################################################################
find_package(GTest 1.10 CONFIG REQUIRED)
include(GoogleTest)
set(PYBIND11_CPP_STANDARD -std=c++17)
find_package(pybind11 2.5 CONFIG REQUIRED)
find_package(Python 3.8 REQUIRED)

################################################################################
# Build sources
################################################################################
enable_testing()
add_subdirectory(libcore)
add_subdirectory(pycore)
