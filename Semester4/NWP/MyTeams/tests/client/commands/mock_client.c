/*
** EPITECH PROJECT, 2022
** Project
** File description:
** mock_client
*/

#include "client.h"

#include <string.h>

void mock_client(client_t *client)
{
    my_cbuffer_init(&client->in_buf, client->raw_in_buf, CLIENT_BUFFER_SIZE);
    my_cbuffer_init(
        &client->out_buf, client->raw_out_buf, CLIENT_BUFFER_SIZE);
    uuid_clear(client->uuid);
    memset(client->name, 0, sizeof(client->name));
}
