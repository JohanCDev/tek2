/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** Unit testing the LEB128 encoding
*/

#include "leb128.h"

#include <criterion/criterion.h>

Test(uleb128_size_32, base)
{
    cr_assert_eq(uleb128_size_32(0), 1);
    cr_assert_eq(uleb128_size_32(42), 1);
    cr_assert_eq(uleb128_size_32(127), 1);
    cr_assert_eq(uleb128_size_32(128), 2);
    cr_assert_eq(uleb128_size_32(142), 2);
    cr_assert_eq(uleb128_size_32(16383), 2);
    cr_assert_eq(uleb128_size_32(16384), 3);
    cr_assert_eq(uleb128_size_32(2097151), 3);
    cr_assert_eq(uleb128_size_32(2097152), 4);
    cr_assert_eq(uleb128_size_32(268435455), 4);
    cr_assert_eq(uleb128_size_32(268435456), 5);
}

Test(uleb128_size_64, base)
{
    cr_assert_eq(uleb128_size_64(0), 1);
    cr_assert_eq(uleb128_size_64(42), 1);
    cr_assert_eq(uleb128_size_64(127), 1);
    cr_assert_eq(uleb128_size_64(128), 2);
    cr_assert_eq(uleb128_size_64(142), 2);
    cr_assert_eq(uleb128_size_64(16383), 2);
    cr_assert_eq(uleb128_size_64(16384), 3);
    cr_assert_eq(uleb128_size_64(2097151), 3);
    cr_assert_eq(uleb128_size_64(2097152), 4);
    cr_assert_eq(uleb128_size_64(268435455), 4);
    cr_assert_eq(uleb128_size_64(268435456), 5);
    cr_assert_eq(uleb128_size_64(45656784566), 6);
    cr_assert_eq(uleb128_size_64(18446744073709551615), 10);
}
