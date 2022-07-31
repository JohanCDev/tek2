set(SRCROOT ${SRCROOT}/server)

add_subdirectory(packets)

set(SRC
    ${SRC}
)

add_myteams_test(
    NAME myteams_server_test
    DISPLAY_NAME "MyTeams-Server-Tests"
    DEPENDENCIES libmyteams_server myteams_util
    SOURCES ${SRC}
)
