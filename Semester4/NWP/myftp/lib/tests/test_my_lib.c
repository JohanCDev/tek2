/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** test_my_lib
*/

#include "../my/my.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(my_str_to_word_array, test_my_str_to_word_array_simple)
{
    char **dest = NULL;
    char src[] = "    test         random string  salt";
    dest = my_str_to_word_array(src, " ");

    cr_assert_str_eq(dest[0], "test");
    cr_assert_str_eq(dest[1], "random");
    cr_assert_str_eq(dest[2], "string");
    cr_assert_str_eq(dest[3], "salt");
}