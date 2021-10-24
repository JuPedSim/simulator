function(print_var variable)
    message(STATUS "${variable}=${${variable}}")
endfunction()

# There is a long outstanding issue with CMake where CMake does not support
# relative paths in CMAKE_PREFIX_PATH but does not report anything. Many hours
# have been wasted over this behavior. We are checking to save your this to
# save everyone some headache. :)
function(check_prefix_path)
    if(CMAKE_PREFIX_PATH)
        foreach(path ${CMAKE_PREFIX_PATH})
            if(NOT IS_ABSOLUTE ${path})
                message(FATAL_ERROR "CMake does not support relative paths for CMAKE_PREFIX_PATH! [${path}]")
            endif()
        endforeach()
    endif()
endfunction()

# This macro ensures that there is always an explicitly set build type.
# If CMAKE_BUILD_TYPE is NOT set during configure, CMAKE_BUILD_TYPE will
# now default to 'Release'
macro(enforce_build_type_is_set)
    set(default_build_type "Release")
    if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
    endif()
endmacro()

# Adds an option to cmake configure to automatically build with clang
# tidy enabled. NOTE: The clang tidy version is explicitly pinned.
macro(add_clang_tidy_support_option)
    option(WITH_TIDY "Build with clang tidy checks enabled (This will increase your build time)" ON)
    if(WITH_TIDY)
        find_program(
            CLANG_TIDY
            NAMES
                clang-tidy-13
                clang-tidy
            REQUIRED
        )
        if(CLANG_TIDY)
            execute_process(
                COMMAND ${CLANG_TIDY} --version
                OUTPUT_VARIABLE clang_tidy_version_output
                ERROR_QUIET
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )
            string(REGEX REPLACE
                ".*LLVM version ([.0-9]+).*"
                "\\1"
                clang_tidy_version
                "${clang_tidy_version_output}"
            )
            if(clang_tidy_version MATCHES "^13.*")
                message(STATUS "Found clang-tidy ${CLANG_TIDY} [${clang_tidy_version}]")
                set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
                set(CMAKE_C_CLANG_TIDY ${CLANG_TIDY})
            else()
                message(FATAL_ERROR "Found clang-tidy but it reports an incorrect version: ${clang_tidy_version}")
            endif()
        endif()
    endif()
endmacro()
