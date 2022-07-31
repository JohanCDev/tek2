set(INCROOT ${SRCROOT}/packets)
set(SRCROOT ${SRCROOT}/packets)

set(SRC
    ${SRC}
    ${SRCROOT}/mock_server.c
    ${INCROOT}/mock_server.h
    ${SRCROOT}/tests_get_messages.c
    ${SRCROOT}/tests_get_teams.c
    ${SRCROOT}/tests_login.c
    ${SRCROOT}/tests_logout.c
    PARENT_SCOPE
)
