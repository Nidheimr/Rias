cmake_minimum_required(VERSION 3.20)
project(Rias C)

# ------------------------------------
# output directory
# ------------------------------------

# this has to account for visual studio DEBUG and RELEASE
# which makes this 3x harder than necessary

set(STD_OUTPUT                              ${CMAKE_SOURCE_DIR}/bin/)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG    ${STD_OUTPUT})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE  ${STD_OUTPUT})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY          ${STD_OUTPUT})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG    ${STD_OUTPUT})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE  ${STD_OUTPUT})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY          ${STD_OUTPUT})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${STD_OUTPUT})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${STD_OUTPUT})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY          ${STD_OUTPUT})

# ------------------------------------
# library target
# ------------------------------------

add_library(Rias STATIC
    src/rias_impl.c
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include/
)

# ------------------------------------
# test target
# ------------------------------------

if (BUILD_TEST_TARGET)
    add_executable(RiasTest src/test.c)
    target_link_libraries(RiasTest Rias)
endif()
