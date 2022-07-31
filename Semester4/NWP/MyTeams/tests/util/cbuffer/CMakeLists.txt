set(SRCROOT ${SRCROOT}/cbuffer)

set(SRC
    ${SRC}
    ${SRCROOT}/test_my_cbuffer_get_parts.c
    ${SRCROOT}/test_my_cbuffer_init.c
    ${SRCROOT}/test_my_cbuffer_pop.c
    ${SRCROOT}/test_my_cbuffer_push.c
    ${SRCROOT}/test_my_cbuffer_read.c
    ${SRCROOT}/test_my_cbuffer_rotate.c
    ${SRCROOT}/test_my_cbuffer_write.c
    PARENT_SCOPE
)
