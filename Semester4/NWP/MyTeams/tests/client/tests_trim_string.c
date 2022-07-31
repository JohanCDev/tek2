/*
** EPITECH PROJECT, 2022
** Project
** File description:
** tests_trim_string
*/

#include "client.h"

#include <criterion/criterion.h>

Test(TrimString, onlySpaces)
{
    char *str = strdup("I     like it        like   that");

    str = trim_string(str);
    cr_assert_str_eq(str, "I like it like that");
}

Test(TrimString, onlyTabs)
{
    char *str =
        strdup("I			like				 it		like	that");

    str = trim_string(str);
    cr_assert_str_eq(str, "I like it like that");
}

Test(TrimString, spacesAndTabs)
{
    char *str = strdup("I  		   like 	it      	  like   	that");

    str = trim_string(str);
    cr_assert_str_eq(str, "I like it like that");
}

Test(TrimString, beforeString)
{
    char *str =
        strdup("	I  		   like 	it      	  like   	that");

    str = trim_string(str);
    cr_assert_str_eq(str, " I like it like that");
}

Test(TrimString, afterString)
{
    char *str =
        strdup("I  		   like 	it      	  like   	that  	");

    str = trim_string(str);
    cr_assert_str_eq(str, "I like it like that ");
}

Test(TrimString, noChanges)
{
    char *str = strdup("I like it like that");

    str = trim_string(str);
    cr_assert_str_eq(str, "I like it like that");
}
