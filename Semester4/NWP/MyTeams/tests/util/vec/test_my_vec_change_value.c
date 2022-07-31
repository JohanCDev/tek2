/*
** EPITECH PROJECT, 2022
** MyTeams - LibMy Excerpt
** File description:
** Tests the my_vec_copy & my_vec_copy_into functions
*/

#include "vec.h"

#include <criterion/criterion.h>

Test(my_vec_change_value, out_of_bounds)
{
    my_vec_t vec;
    short value = 42;

    my_vec_init(&vec, sizeof(short));
    cr_assert_eq(MY_VEC_OUT_OF_BOUNDS, my_vec_change_value(&vec, &value, 0));
    cr_assert_eq(MY_VEC_OUT_OF_BOUNDS, my_vec_change_value(&vec, &value, 10));
}

Test(my_vec_change_value, normal)
{
    my_vec_t vec;
    unsigned long long value = 42;

    my_vec_init_capacity(&vec, 1, sizeof(unsigned long long));
    my_vec_push(&vec, &value);
    value = 1234;
    cr_assert_eq(MY_VEC_OK, my_vec_change_value(&vec, &value, 0));
    cr_assert_eq(1234, MY_VEC_GET_ELEM(unsigned long long, &vec, 0));
    my_vec_free(&vec, NULL);
}
