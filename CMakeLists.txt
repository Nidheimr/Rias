cmake_minimum_required(VERSION 3.20)
project(Rias C)

# ------------------------------------
# output directory
# ------------------------------------

# this has to account for visual studio DEBUG and RELEASE
# which makes this 3x harder than necessary

set(STD_OUTPUT                     ${CMAKE_SOURCE_DIR}/bin/)

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

set(SRC_FILES
    src/rias_impl.c
)

add_library(libRias STATIC ${SRC_FILES})
set_target_properties(libRias PROPERTIES 
    PREFIX      "lib"
    OUTPUT_NAME "Rias"
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include/
)

# ------------------------------------
# test target
# ------------------------------------

if (BUILD_TEST_TARGET)
    add_executable(testRias src/test.c)
    set_target_properties(testRias PROPERTIES
        PREFIX      "test"
        OUTPUT_NAME "Rias"
    )
    target_link_libraries(testRias libRias)
endif()
