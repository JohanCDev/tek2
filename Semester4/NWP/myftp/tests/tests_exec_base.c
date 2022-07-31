/*
** EPITECH PROJECT, 2021
** Duo-7
** File description:
** tests
*/

#include "execution.h"
#include "client.h"
#include <criterion/criterion.h>

Test(test_exec_user, exec_user)
{
    client_t cli = {.log = NO_ST, .cli_fd = 1, .path = "~"};
    client_t cli2 = {.log = NO_ST, .cli_fd = 2, .path = "~"};
    char const *commands[3] = {"USER", "Anonymous", NULL};
    char const *commands2[3] = {"USER", "Roger", NULL};
    char const *commands3[2] = {"USER", NULL};

    exec_user(&cli, commands);
    exec_user(&cli2, commands2);
    exec_user(&cli2, commands3);
    cr_assert_eq(cli.log, ANO_ST);
    cr_assert_eq(cli2.log, USER_ST);
}

Test(test_exec_pass, exec_pass)
{
    client_t cli = {.log = ANO_ST, .cli_fd = 1, .path = "~"};
    client_t cli2 = {.log = USER_ST, .cli_fd = 2, .path = "~"};
    client_t cli3 = {.log = NO_ST, .cli_fd = 3, .path = "~"};
    char const *commands[2] = {"PASS", NULL};
    char const *commands2[3] = {"PASS", "HEY", NULL};

    exec_pass(&cli, commands);
    exec_pass(&cli2, commands2);
    exec_pass(&cli3, commands2);
    exec_pass(&cli3, commands);
    cr_assert_eq(cli.log, LOGGED_ST);
    cr_assert_eq(cli2.log, USER_ST);
    cr_assert_eq(cli3.log, NO_ST);
}

Test(test_exec_quit, exec_quit)
{
    client_t cli = {.log = LOGGED_ST, .cli_fd = 1, .path = "~"};
    client_t cli2 = {.log = USER_ST, .cli_fd = 2, .path = "~"};
    char const *commands[2] = {"QUIT", NULL};
    char const *commands2[3] = {"QUIT", "RONDOUDOU", NULL};

    exec_quit(&cli, commands);
    exec_quit(&cli2, commands2);
    cr_assert_eq(cli.log, DISC_ST);
    cr_assert_eq(cli2.log, USER_ST);
    exec_quit(&cli, commands2);
    exec_quit(&cli2, commands);
}

Test(test_exec_noop, exec_noop)
{
    client_t cli = {.log = LOGGED_ST, .cli_fd = 1, .path = "~"};
    client_t cli2 = {.log = USER_ST, .cli_fd = 2, .path = "~"};
    char const *commands[2] = {"QUIT", NULL};
    char const *commands2[3] = {"QUIT", "RONDOUDOU", NULL};

    exec_noop(&cli, commands);
    exec_noop(&cli2, commands2);
    cr_assert_eq(cli.log, LOGGED_ST);
    cr_assert_eq(cli2.log, USER_ST);
    exec_noop(&cli, commands2);
    exec_noop(&cli2, commands);
}