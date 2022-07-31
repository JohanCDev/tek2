/*
** EPITECH PROJECT, 2022
** Project
** File description:
** tests_handle_command
*/

#include "commands/commands.h"

#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(CommandClient, not_a_command, .init = cr_redirect_stdout)
{
    char command[] = "idk";
    client_t client = {0};
    client.sock_fd = STDOUT_FILENO;

    handle_command(&client, command);
    fflush(stdout);
    cr_assert_stdout_eq_str("Not a command.\n");
}

Test(CommandClient, command_without_prefix, .init = cr_redirect_stdout)
{
    char command[] = "help";
    client_t client = {0};
    client.sock_fd = STDOUT_FILENO;

    handle_command(&client, command);
    fflush(stdout);
    cr_assert_stdout_eq_str("Not a command.\n");
}

Test(CommandClient, unknown_command, .init = cr_redirect_stdout)
{
    char command[] = "/idk";
    client_t client = {0};
    client.sock_fd = STDOUT_FILENO;

    handle_command(&client, command);
    fflush(stdout);
    cr_assert_stdout_eq_str("/idk: Unknown command.\n");
}

Test(CommandClient, print_helper_of_command, .init = cr_redirect_stdout)
{
    char command[] = "/help help";
    client_t client = {0};
    client.sock_fd = STDOUT_FILENO;

    handle_command(&client, command);
    fflush(stdout);
    cr_assert_stdout_eq_str("/help: Display available commands\n");
}

Test(HandleCommand, with_spaces_in_quotes, .init = cr_redirect_stdout)
{
    char command[] = "/login \"I like it like that\"";
    size_t size = 0;
    char result[23] = "123456789012345678901MM";
    client_t client = {0};
    client.sock_fd = STDOUT_FILENO;

    handle_command(&client, command);
    fflush(stdout);
    size = fread(result, sizeof(char), 22, cr_get_redirected_stdout());
    cr_assert_eq(size, 21);
    cr_assert_arr_eq(result, "\000\023I like it like thatM", 22);
}
