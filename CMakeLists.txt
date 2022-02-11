cmake_minimum_required(VERSION 3.5)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

project(flexgrep)


include(GNUInstallDirs)

# VARIABLES
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR}/include/flexgrep")


IF (WIN32)
    # Generate symbold pdb files if in debug mode
    add_compile_options("$<$<CONFIG:DEBUG>:/Zi>")
    add_link_options("$<$<CONFIG:DEBUG>:/DEBUG>")
    add_link_options("$<$<CONFIG:DEBUG>:/OPT:REF>")
    add_link_options("$<$<CONFIG:DEBUG>:/OPT:ICF>")
ENDIF ()


add_subdirectory(src)
add_subdirectory(tests)
