/*
** EPITECH PROJECT, 2022
** Project
** File description:
** tests_login
*/

#include "commands/commands.h"
#include "client.h"
#include "mock_client.h"

#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(packetLogin, simple)
{
    client_t client;
    uint32_t type;
    uint32_t len;
    char name[MAX_NAME_LENGTH] = {0};

    mock_client(&client);
    command_login(&client, "\"Jack\"");
    my_cbuffer_pop_front_uleb128_32(&client.out_buf, &type);
    my_cbuffer_pop_front_uleb128_32(&client.out_buf, &len);
    my_cbuffer_pop_front(&client.out_buf, name, len);
    cr_expect_eq(client.out_buf.len, 0);
    cr_expect_eq(type, C2S_LOGIN);
    cr_expect_eq(len, 4);
    cr_expect_str_eq(client.name, "Jack");
    cr_expect_str_eq(name, "Jack");
}
