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
# Compilation flags
################################################################################
# Note: Setting global compile flags via CMAKE_CXX_FLAGS has the drawback that
#       generator expressions cannot be used. This leads to all kind of
#       conditional adding of flags. It is generally preferable to use generator
#       expresssions.
#
# WARNING: Do not break the lines, each option has to be on its own line or
#          CMake will enclose multiple flags in '' which the compiler then
#          treats as a single flag and does not understand.
list(APPEND COMMON_COMPILE_OPTIONS
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wall>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wextra>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wpedantic>
#        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Werror>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wconversion>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wimplicit-fallthrough>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wsign-conversion>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-fdiagnostics-color=always>
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
#        $<$<CXX_COMPILER_ID:MSVC>:/WX>
        $<$<CXX_COMPILER_ID:MSVC>:/EHsc>
        -fPIC
)

################################################################################
# Dependencies
################################################################################
find_package(GTest 1.10 CONFIG REQUIRED)
include(GoogleTest)
set(PYBIND11_CPP_STANDARD -std=c++17)
find_package(pybind11 2.5 CONFIG REQUIRED)
find_package(Python 3.8 REQUIRED)
find_package(fmt 7.1 CONFIG REQUIRED)

################################################################################
# Build sources
################################################################################
enable_testing()
add_subdirectory(libcore)
add_subdirectory(pycore)
