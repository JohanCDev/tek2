set(INCROOT ${SRCROOT}/client)
set(SRCROOT ${SRCROOT}/client)

add_subdirectory(commands)

set(SRC
    ${SRC}
    ${SRCROOT}/tests_trim_string.c
)

add_myteams_test(
    INCLUDE_DIRECTORIES ${INCROOT}
    NAME myteams_client_test
    DISPLAY_NAME "MyTeams-Client-Tests"
    DEPENDENCIES libmyteams_cli myteams_util uuid
    SOURCES ${SRC}
)
