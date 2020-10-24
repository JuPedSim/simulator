cmake_minimum_required(VERSION 3.14)
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
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
endif()

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
