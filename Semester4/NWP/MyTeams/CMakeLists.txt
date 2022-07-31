cmake_minimum_required(VERSION 3.17.0)

project(MyTeams LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# Add ./cmake to the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_compile_options(
    "-Wall" "-Wextra" "-Wshadow" "-pedantic" "-Wpointer-arith"
    "$<$<CONFIG:RELEASE>:-O3;-Werror>"
    "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

# Define the logging library located in the 'libs/myteams' folder
add_library(myteams_logging SHARED IMPORTED)

set_target_properties(myteams_logging PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/libs/myteams
    IMPORTED_NO_SONAME TRUE
    IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/libs/myteams/libmyteams.so
)

include (TestBigEndian)

TEST_BIG_ENDIAN(MYTEAMS_IS_BIG_ENDIAN)
if (MYTEAMS_IS_BIG_ENDIAN)
    add_compile_definitions(MYTEAMS_ENDIAN=MYTEAMS_BIG_ENDIAN)
else()
    add_compile_definitions(MYTEAMS_ENDIAN=MYTEAMS_LITTLE_ENDIAN)
endif()

add_subdirectory(src)

# Unit testing
if (BUILD_TEST_SUITE)
    # Check for criterion
    find_package(Criterion REQUIRED)
    enable_testing()
    add_subdirectory(tests)
endif()
