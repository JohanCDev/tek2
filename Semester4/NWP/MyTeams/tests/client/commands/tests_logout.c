/*
** EPITECH PROJECT, 2022
** Project
** File description:
** tests_login
*/

#include "client.h"
#include "commands/commands.h"
#include "mock_client.h"

#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(packetLogout, simple)
{
    client_t client;
    uint32_t type;
    uint32_t len;

    mock_client(&client);
    command_logout(&client, "");
    my_cbuffer_pop_front_uleb128_32(&client.out_buf, &type);
    my_cbuffer_pop_front_uleb128_32(&client.out_buf, &len);
    cr_expect_eq(client.out_buf.len, 0);
    cr_expect_eq(type, C2S_LOGOUT);
    cr_expect_eq(len, 0);
}
