/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** Unit testing the LEB128 encoding
*/

#include "leb128.h"

#include <criterion/criterion.h>

Test(uleb128_decode_32, base)
{
    uint32_t result;

    cr_expect_eq(uleb128_decode_32("\x00", &result), 1);
    cr_expect_eq(result, 0);
    cr_expect_eq(uleb128_decode_32("\x2a", &result), 1);
    cr_expect_eq(result, 42);
    cr_expect_eq(uleb128_decode_32("\xff\xff\xff\xff\xf", &result), 5);
    cr_expect_eq(result, UINT32_MAX);
}

Test(uleb128_decode_64, base)
{
    uint64_t result;

    cr_expect_eq(uleb128_decode_64("\x00", &result), 1);
    cr_expect_eq(result, 0);
    cr_expect_eq(uleb128_decode_64("\x2a", &result), 1);
    cr_expect_eq(result, 42);
    cr_expect_eq(uleb128_decode_64("\xff\xff\xff\xff\xf", &result), 5);
    cr_expect_eq(result, UINT32_MAX);
}
