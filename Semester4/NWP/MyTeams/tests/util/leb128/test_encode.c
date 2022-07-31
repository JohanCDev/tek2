/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** Unit testing the LEB128 encoding
*/

#include "leb128.h"

#include <criterion/criterion.h>

Test(uleb128_encode_32, zero)
{
    unsigned char buf[] = "01234";

    cr_expect_eq(uleb128_encode_32(buf, 0), 1);
    cr_expect_eq(buf[0], 0);
    cr_expect_eq(buf[1], '1');
    cr_expect_eq(buf[2], '2');
    cr_expect_eq(buf[3], '3');
    cr_expect_eq(buf[4], '4');
    cr_expect_eq(buf[5], '\0');
}

Test(uleb128_encode_32, one_byte)
{
    unsigned char buf[] = "01234";

    cr_expect_eq(uleb128_encode_32(buf, 42), 1);
    cr_expect_eq(buf[0], 42);
    cr_expect_eq(buf[1], '1');
    cr_expect_eq(buf[2], '2');
    cr_expect_eq(buf[3], '3');
    cr_expect_eq(buf[4], '4');
    cr_expect_eq(buf[5], '\0');
    cr_expect_eq(uleb128_encode_32(buf, 0x7f), 1);
    cr_expect_eq(buf[0], 0x7f);
    cr_expect_eq(buf[1], '1');
    cr_expect_eq(buf[2], '2');
    cr_expect_eq(buf[3], '3');
    cr_expect_eq(buf[4], '4');
    cr_expect_eq(buf[5], '\0');
}

Test(uleb128_encode_32, three_bytes)
{
    unsigned char buf[] = "01234";

    cr_expect_eq(uleb128_encode_32(buf, 624485), 3);
    cr_expect_eq(buf[0], 0xe5);
    cr_expect_eq(buf[1], 0x8e);
    cr_expect_eq(buf[2], 0x26);
    cr_expect_eq(buf[3], '3');
    cr_expect_eq(buf[4], '4');
    cr_expect_eq(buf[5], '\0');
}

Test(uleb128_encode_32, five_bytes)
{
    unsigned char buf[] = "01234";

    cr_expect_eq(uleb128_encode_32(buf, UINT32_MAX), 5);
    cr_expect_eq(buf[0], 0xff);
    cr_expect_eq(buf[1], 0xff);
    cr_expect_eq(buf[2], 0xff);
    cr_expect_eq(buf[3], 0xff);
    cr_expect_eq(buf[4], 0x0f);
    cr_expect_eq(buf[5], '\0');
}

Test(uleb128_encode_64, zero)
{
    unsigned char buf[] = "01234";

    cr_expect_eq(uleb128_encode_64(buf, 0), 1);
    cr_expect_eq(buf[0], 0);
    cr_expect_eq(buf[1], '1');
    cr_expect_eq(buf[2], '2');
    cr_expect_eq(buf[3], '3');
    cr_expect_eq(buf[4], '4');
    cr_expect_eq(buf[5], '\0');
}

Test(uleb128_encode_64, one_byte)
{
    unsigned char buf[] = "01234";

    cr_expect_eq(uleb128_encode_64(buf, 42), 1);
    cr_expect_eq(buf[0], 42);
    cr_expect_eq(buf[1], '1');
    cr_expect_eq(buf[2], '2');
    cr_expect_eq(buf[3], '3');
    cr_expect_eq(buf[4], '4');
    cr_expect_eq(buf[5], '\0');
    cr_expect_eq(uleb128_encode_64(buf, 0x7f), 1);
    cr_expect_eq(buf[0], 0x7f);
    cr_expect_eq(buf[1], '1');
    cr_expect_eq(buf[2], '2');
    cr_expect_eq(buf[3], '3');
    cr_expect_eq(buf[4], '4');
    cr_expect_eq(buf[5], '\0');
}

Test(uleb128_encode_64, three_bytes)
{
    unsigned char buf[] = "01234";

    cr_expect_eq(uleb128_encode_64(buf, 624485), 3);
    cr_expect_eq(buf[0], 0xe5);
    cr_expect_eq(buf[1], 0x8e);
    cr_expect_eq(buf[2], 0x26);
    cr_expect_eq(buf[3], '3');
    cr_expect_eq(buf[4], '4');
    cr_expect_eq(buf[5], '\0');
}

Test(uleb128_encode_64, five_bytes)
{
    unsigned char buf[] = "01234";

    cr_expect_eq(uleb128_encode_32(buf, UINT32_MAX), 5);
    cr_expect_eq(buf[0], 0xff);
    cr_expect_eq(buf[1], 0xff);
    cr_expect_eq(buf[2], 0xff);
    cr_expect_eq(buf[3], 0xff);
    cr_expect_eq(buf[4], 0x0f);
    cr_expect_eq(buf[5], '\0');
}
