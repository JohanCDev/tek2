set(INCROOT ${INCROOT}/commands)
set(SRCROOT ${SRCROOT}/commands)

set(SRC
    ${SRC}
    ${SRCROOT}/mock_client.c
    ${INCROOT}/mock_client.h
    ${SRCROOT}/tests_login.c
    ${SRCROOT}/tests_logout.c
    PARENT_SCOPE
)
