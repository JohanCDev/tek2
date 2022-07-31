set(SRCROOT ${SRCROOT}/hash_map)

set(SRC
    ${SRC}
    ${SRCROOT}/test_my_hash_map_contains.c
    ${SRCROOT}/test_my_hash_map_drop.c
    ${SRCROOT}/test_my_hash_map_get.c
    ${SRCROOT}/test_my_hash_map_init.c
    ${SRCROOT}/test_my_hash_map_insert.c
    ${SRCROOT}/test_my_hash_map_iter.c
    ${SRCROOT}/test_my_hash_map_remove.c
    PARENT_SCOPE
)
