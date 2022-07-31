/*
** EPITECH PROJECT, 2022
** MyTeams - LibMy Excerpt
** File description:
** Tests the my_cbuffer_pop_* functions
*/

#include "cbuffer.h"

#include <criterion/criterion.h>

Test(my_cbuffer_pop_front, full_buffer_contiguous1)
{
    my_cbuffer_t buf = {"abcdefhij", 10, 10, 0, 0};
    char dst[11] = {0};

    cr_assert_eq(my_cbuffer_pop_front(&buf, dst, 10), dst);
    cr_assert_str_eq(dst, "abcdefhij");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 0);
    cr_assert_eq(buf.tail, 0);
    cr_assert_eq(buf.head, 0);
}

Test(my_cbuffer_pop_front, full_buffer_contiguous2)
{
    my_cbuffer_t buf = {"abcdefhij", 10, 10, 0, 0};
    char dst[11] = {0};

    cr_assert_eq(my_cbuffer_pop_front(&buf, dst, 4), dst);
    cr_assert_str_eq(dst, "abcd");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 6);
    cr_assert_eq(buf.tail, 4);
    cr_assert_eq(buf.head, 0);
}

Test(my_cbuffer_pop_front, full_buffer_split1)
{
    my_cbuffer_t buf = {"hijabcdefg", 10, 10, 3, 3};
    char dst[11] = {0};

    cr_assert_eq(my_cbuffer_pop_front(&buf, dst, 10), dst);
    cr_assert_str_eq(dst, "abcdefghij");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 0);
    cr_assert_eq(buf.tail, 3);
    cr_assert_eq(buf.head, 3);
}

Test(my_cbuffer_pop_front, full_buffer_split2)
{
    my_cbuffer_t buf = {"hijabcdefg", 10, 10, 3, 3};
    char dst[11] = {0};

    cr_assert_eq(my_cbuffer_pop_front(&buf, dst, 4), dst);
    cr_assert_str_eq(dst, "abcd");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 6);
    cr_assert_eq(buf.tail, 7);
    cr_assert_eq(buf.head, 3);
}

Test(my_cbuffer_pop_front, partial_buffer_contiguous1)
{
    my_cbuffer_t buf = {"012345abc9", 10, 3, 6, 9};
    char dst[11] = "TestString";

    cr_assert_eq(my_cbuffer_pop_front(&buf, dst, 3), dst);
    cr_assert_str_eq(dst, "abctString");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 0);
    cr_assert_eq(buf.tail, 9);
    cr_assert_eq(buf.head, 9);
}

Test(my_cbuffer_pop_front, partial_buffer_contiguous2)
{
    my_cbuffer_t buf = {"012345abc9", 10, 3, 6, 9};
    char dst[11] = "TestString";

    cr_assert_eq(my_cbuffer_pop_front(&buf, dst, 1), dst);
    cr_assert_str_eq(dst, "aestString");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 2);
    cr_assert_eq(buf.tail, 7);
    cr_assert_eq(buf.head, 9);
}

Test(my_cbuffer_pop_front, partial_buffer_split1)
{
    my_cbuffer_t buf = {"bc2345678a", 10, 3, 9, 2};
    char dst[11] = "TestString";

    cr_assert_eq(my_cbuffer_pop_front(&buf, dst, 3), dst);
    cr_assert_str_eq(dst, "abctString");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 0);
    cr_assert_eq(buf.tail, 2);
    cr_assert_eq(buf.head, 2);
}

Test(my_cbuffer_pop_front, partial_buffer_split2)
{
    my_cbuffer_t buf = {"bc2345678a", 10, 3, 9, 2};
    char dst[11] = "TestString";

    cr_assert_eq(my_cbuffer_pop_front(&buf, dst, 1), dst);
    cr_assert_str_eq(dst, "aestString");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 2);
    cr_assert_eq(buf.tail, 0);
    cr_assert_eq(buf.head, 2);
}

Test(my_cbuffer_pop_front_uleb128_32, full_buffer_contiguous)
{
    my_cbuffer_t buf = {"\xe5\x8e\x26\0\0\0\0\0\0\0", 10, 10, 0, 0};
    uint32_t result;

    cr_assert(my_cbuffer_pop_front_uleb128_32(&buf, &result));
    cr_assert_eq(result, 624485);
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 7);
    cr_assert_eq(buf.tail, 3);
    cr_assert_eq(buf.head, 0);
}

Test(my_cbuffer_pop_front_uleb128_32, truncated)
{
    my_cbuffer_t buf = {"\xe5\x8e", 2, 2, 0, 0};
    uint32_t result;

    cr_assert(!my_cbuffer_pop_front_uleb128_32(&buf, &result));
    cr_assert_eq(buf.cap, 2);
    cr_assert_eq(buf.len, 2);
    cr_assert_eq(buf.tail, 0);
    cr_assert_eq(buf.head, 0);
}

Test(my_cbuffer_pop_back, full_buffer_contiguous1)
{
    my_cbuffer_t buf = {"abcdefghij", 10, 10, 0, 0};
    char dst[11] = {0};

    cr_assert_eq(my_cbuffer_pop_back(&buf, dst, 10), dst);
    cr_assert_str_eq(dst, "abcdefghij");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 0);
    cr_assert_eq(buf.tail, 0);
    cr_assert_eq(buf.head, 0);
}

Test(my_cbuffer_pop_back, full_buffer_contiguous2)
{
    my_cbuffer_t buf = {"abcdefghij", 10, 10, 0, 0};
    char dst[11] = {0};

    cr_assert_eq(my_cbuffer_pop_back(&buf, dst, 4), dst);
    cr_assert_str_eq(dst, "ghij");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 6);
    cr_assert_eq(buf.tail, 0);
    cr_assert_eq(buf.head, 6);
}

Test(my_cbuffer_pop_back, full_buffer_split1)
{
    my_cbuffer_t buf = {"hijabcdefg", 10, 10, 3, 3};
    char dst[11] = {0};

    cr_assert_eq(my_cbuffer_pop_back(&buf, dst, 10), dst);
    cr_assert_str_eq(dst, "abcdefghij");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 0);
    cr_assert_eq(buf.tail, 3);
    cr_assert_eq(buf.head, 3);
}

Test(my_cbuffer_pop_back, full_buffer_split2)
{
    my_cbuffer_t buf = {"hijabcdefg", 10, 10, 3, 3};
    char dst[11] = {0};

    cr_assert_eq(my_cbuffer_pop_back(&buf, dst, 4), dst);
    cr_assert_str_eq(dst, "ghij");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 6);
    cr_assert_eq(buf.tail, 3);
    cr_assert_eq(buf.head, 9);
}

Test(my_cbuffer_pop_back, partial_buffer_contiguous1)
{
    my_cbuffer_t buf = {"012345abc9", 10, 3, 6, 9};
    char dst[11] = "TestString";

    cr_assert_eq(my_cbuffer_pop_back(&buf, dst, 3), dst);
    cr_assert_str_eq(dst, "abctString");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 0);
    cr_assert_eq(buf.tail, 6);
    cr_assert_eq(buf.head, 6);
}

Test(my_cbuffer_pop_back, partial_buffer_contiguous2)
{
    my_cbuffer_t buf = {"012345abc9", 10, 3, 6, 9};
    char dst[11] = "TestString";

    cr_assert_eq(my_cbuffer_pop_back(&buf, dst, 1), dst);
    cr_assert_str_eq(dst, "cestString");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 2);
    cr_assert_eq(buf.tail, 6);
    cr_assert_eq(buf.head, 8);
}

Test(my_cbuffer_pop_back, partial_buffer_split1)
{
    my_cbuffer_t buf = {"bc2345678a", 10, 3, 9, 2};
    char dst[11] = "TestString";

    cr_assert_eq(my_cbuffer_pop_back(&buf, dst, 3), dst);
    cr_assert_str_eq(dst, "abctString");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 0);
    cr_assert_eq(buf.tail, 9);
    cr_assert_eq(buf.head, 9);
}

Test(my_cbuffer_pop_back, partial_buffer_split2)
{
    my_cbuffer_t buf = {"bc2345678a", 10, 3, 9, 2};
    char dst[11] = "TestString";

    cr_assert_eq(my_cbuffer_pop_back(&buf, dst, 1), dst);
    cr_assert_str_eq(dst, "cestString");
    cr_assert_eq(buf.cap, 10);
    cr_assert_eq(buf.len, 2);
    cr_assert_eq(buf.tail, 9);
    cr_assert_eq(buf.head, 1);
}
