cmake_minimum_required(VERSION 3.20)
project(Rias C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------
# output directory
# ------------------------------------

set(STD_OUTPUT                              ${CMAKE_SOURCE_DIR}/bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY          ${STD_OUTPUT})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${STD_OUTPUT})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${STD_OUTPUT})

# ------------------------------------
# executable
# ------------------------------------

add_executable(Rias
    src/main.c
    src/rias_impl.c
)

target_include_directories(Rias PRIVATE
    ${CMAKE_SOURCE_DIR}/include/
)
