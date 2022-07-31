set(SRCROOT ${SRCROOT}/util)

add_subdirectory(cbuffer)
add_subdirectory(hash)
add_subdirectory(hash_map)
add_subdirectory(leb128)
add_subdirectory(vec)

set(SRC
    ${SRC}
    PARENT_SCOPE
)

add_myteams_test(
    NAME myteams_util_test
    DISPLAY_NAME "MyTeams-Utility-Tests"
    DEPENDENCIES myteams_util
    SOURCES ${SRC}
)
