set(${INCROOT} ${PROJECT_SOURCE_DIR}/include/)
set(${SRCROOT} ${PROJECT_SOURCE_DIR}/src/)

set(SRC
    ${SRCROOT}hello_world.c
)

add_subdirectory(lib)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC ikea)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})