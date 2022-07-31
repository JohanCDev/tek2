/*
** EPITECH PROJECT, 2022
** MyTeams - LibMy Excerpt
** File description:
** Tests the my_cbuffer_init function
*/

#include "cbuffer.h"

#include <criterion/criterion.h>

Test(my_cbuffer_init, normal)
{
    char *mem = "test";
    my_cbuffer_t buf;

    my_cbuffer_init(&buf, mem, 4);
    cr_assert_eq(buf.data, mem);
    cr_assert_eq(buf.cap, 4);
    cr_assert_eq(buf.len, 0);
    cr_assert_eq(buf.tail, 0);
    cr_assert_eq(buf.head, 0);
}
