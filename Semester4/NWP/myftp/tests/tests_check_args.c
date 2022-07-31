/*
** EPITECH PROJECT, 2021
** Duo-7
** File description:
** tests
*/

#include <criterion/criterion.h>
#include <stdio.h>

short unsigned int check_args(int argc, char const **argv);

Test(test_check_args, check_args)
{
    int argc = 2;
    int argc2 = 3;
    char const *argv[2] = {"./myftp", "-help"};
    char const *argv2[2] = {"./myftp", "zpjaz"};
    char const *argv3[2] = {"./myftp", "80"};
    char const *argv4[2] = {"./myftp", "aopjazf"};
    char const *argv5[3] = {"./myftp", "aopjazf", "zgzg"};
    char const *argv6[3] = {"./myftp", "89", "zgzg"};


    int ret = check_args(argc, argv);
    puts("\n\n\n");
    printf("%d\n", ret);
    cr_assert_eq(ret, 2);
    ret = check_args(argc, argv2);
    cr_assert_eq(ret, 1);
    ret = check_args(argc, argv4);
    cr_assert_eq(ret, 1);
    ret = check_args(argc, argv4);
    cr_assert_eq(ret, 1);
    ret = check_args(argc2, argv5);
    cr_assert_eq(ret, 1);
    ret = check_args(argc2, argv6);
    cr_assert_eq(ret, 1);
}