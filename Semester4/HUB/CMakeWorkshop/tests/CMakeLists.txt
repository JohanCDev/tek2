set(SRCROOT ${PROJECT_SOURCE_DIR}/tests/)

set(SRC
    ${SRCROOT}test_ikea.c
)

set(TARGET_NAME unit_test)

add_executable(${TARGET_NAME} ${SRC})

set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

target_link_libraries(${TARGET_NAME} PRIVATE ikea ${CRITERION_LIBRARIES})

# On MacOS, we must tell CMake to search in /opt/hombrew/include for Criterion headers.
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_include_directories(${TARGET_NAME} PRIVATE /opt/homebrew/include)
endif()

add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
