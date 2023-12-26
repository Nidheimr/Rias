cmake_minimum_required(VERSION 3.20)
project(Rias C)

# ------------------------------------
# output directory
# ------------------------------------

set(STD_OUTPUT                     ${CMAKE_SOURCE_DIR}/bin/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${STD_OUTPUT})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${STD_OUTPUT})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${STD_OUTPUT})

# ------------------------------------
# library
# ------------------------------------

add_library(Rias STATIC
    src/rias_impl.c
)

target_include_directories(Rias PRIVATE
    ${CMAKE_SOURCE_DIR}/include/
)
