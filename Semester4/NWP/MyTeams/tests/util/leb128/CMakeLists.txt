set(SRCROOT ${SRCROOT}/leb128)

set(SRC
    ${SRC}
    ${SRCROOT}/test_decode.c
    ${SRCROOT}/test_encode.c
    ${SRCROOT}/test_size.c
    PARENT_SCOPE
)
