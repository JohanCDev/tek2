set(SRCROOT "${PROJECT_SOURCE_DIR}/tests")

function(add_myteams_test)
    # Declare arguments
    set(oneValueArgs NAME DISPLAY_NAME)
    set(multiValueArgs INCLUDE_DIRS SOURCES DEPENDENCIES)
    cmake_parse_arguments(add_myteams_test "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Check for required arguments NAME and SOURCES
    if (NOT DEFINED add_myteams_test_NAME)
        message(FATAL_ERROR "missing unit test name")
    endif()
    if (NOT DEFINED add_myteams_test_SOURCES)
        message(FATAL_ERROR "missing unit test sources")
    endif()
    if (NOT DEFINED add_myteams_test_DEPENDENCIES)
        message(FATAL_ERROR "missing unit test dependencies")
    endif()

    # Define shorthand variables
    set(TARGET_NAME ${add_myteams_test_NAME})
    set(SRC ${add_myteams_test_SOURCES})
    set(INCDIRS ${add_myteams_test_INCLUDE_DIRS})
    set(WORKING_DIRECTORY ${add_myteams_test_WORKING_DIRECTORY})
    set(DEPS ${add_myteams_test_DEPENDENCIES})

    if (DEFINED add_myteams_test_DISPLAY_NAME)
        set(DISPLAY_NAME ${add_myteams_test_DISPLAY_NAME})
    else()
        set(DISPLAY_NAME ${TARGET_NAME})
    endif()

    # Create the test executable
    add_executable(${TARGET_NAME} ${SRC})
    target_include_directories(${TARGET_NAME} PRIVATE ${INCDIRS})

    source_group(${TARGET_NAME} FILES ${SRC})
    set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "tests")

    if (CMAKE_COMPILER_IS_GNUCC)
        target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra)
    endif()

    target_link_libraries(${TARGET_NAME} PRIVATE ${DEPS} ${CRITERION_LIBRARIES})

    # On MacOS, we must tell CMake to search in /opt/hombrew/include for Criterion headers.
    if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        target_include_directories(${TARGET_NAME} PRIVATE /opt/homebrew/include)
    endif()

    # Register the test
    add_test(NAME "${DISPLAY_NAME}" COMMAND ${TARGET_NAME} WORKING_DIRECTORY ${WORKING_DIRECTORY})
endfunction()

add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(util)
