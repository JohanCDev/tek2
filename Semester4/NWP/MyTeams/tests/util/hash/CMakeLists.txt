set(SRCROOT ${SRCROOT}/hash)

set(SRC
    ${SRC}
    ${SRCROOT}/test_my_hasher_finish.c
    ${SRCROOT}/test_my_hasher_init.c
    ${SRCROOT}/test_my_hasher_write.c
    ${SRCROOT}/test_my_hasher_write_fixed_int.c
    ${SRCROOT}/test_my_hasher_write_int.c
    ${SRCROOT}/test_my_hash_load_from_mem.c
    ${SRCROOT}/test_my_siphash13_rounds.c
    PARENT_SCOPE
)
