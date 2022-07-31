/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** tests_login
*/

#include "protocol.h"
#include "server.h"
#include "mock_server.h"
#include "packet_handlers.h"

#include <uuid/uuid.h>
#include <criterion/criterion.h>

Test(login_packet, empty_name)
{
    server_t server;
    peer_t *peer = mock_server(&server);
    mock_generic_packet_t response;

    cr_assert_eq(handle_login_packet(peer, 0), PRESULT_OK);
    mock_parse_generic(peer, &response);
    cr_expect_eq(peer->out_buf.len, 0);
    cr_expect_eq(response.type, S2C_GENERIC);
    cr_expect_eq(response.code, REPLY_INVALID_LENGTH);
    cr_expect_str_eq(response.description, "invalid name length");
    server_destroy(&server);
}

Test(login_packet, too_long_name)
{
    server_t server;
    peer_t *peer = mock_server(&server);
    mock_generic_packet_t response;

    cr_assert_eq(handle_login_packet(peer, MAX_NAME_LENGTH * 2), PRESULT_OK);
    mock_parse_generic(peer, &response);
    cr_expect_eq(peer->out_buf.len, 0);
    cr_expect_eq(response.type, S2C_GENERIC);
    cr_expect_eq(response.code, REPLY_INVALID_LENGTH);
    cr_expect_str_eq(response.description, "invalid name length");
    server_destroy(&server);
}

Test(login_packet, valid)
{
    server_t server;
    peer_t *peer = mock_server(&server);
    uint32_t type;
    uint32_t len;
    uuid_t id;
    uuid_t id2;
    uuid_t id3;
    char name1[MAX_NAME_LENGTH] = {0};
    char name2[MAX_NAME_LENGTH] = {0};
    char name3[MAX_NAME_LENGTH] = {0};

    my_cbuffer_push_back(&peer->in_buf, "bobby", 5);
    cr_assert_eq(handle_login_packet(peer, 5), PRESULT_OK);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &type);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &len);
    my_cbuffer_pop_front(&peer->out_buf, id, sizeof(uuid_t));
    my_cbuffer_pop_front(&peer->out_buf, name1, len - sizeof(uuid_t));
    cr_expect_eq(peer->out_buf.len, 0);
    cr_expect_eq(type, S2C_LOGIN);
    cr_expect_eq(len, 21);
    cr_expect_str_eq(name1, "bobby");
    cr_expect_eq(peer->in_buf.len, 0);

    my_cbuffer_push_back(&peer->in_buf, "bobby", 5);
    cr_assert_eq(handle_login_packet(peer, 5), PRESULT_OK);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &type);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &len);
    my_cbuffer_pop_front(&peer->out_buf, id2, sizeof(uuid_t));
    my_cbuffer_pop_front(&peer->out_buf, name2, len - sizeof(uuid_t));
    cr_expect_eq(peer->out_buf.len, 0);
    cr_expect_eq(type, S2C_LOGIN);
    cr_expect_eq(len, 21);
    cr_expect_str_eq(name2, "bobby");
    cr_expect_eq(peer->in_buf.len, 0);
    cr_assert_eq(uuid_compare(id, id2), 0);

    my_cbuffer_push_back(&peer->in_buf, "tables", 6);
    cr_assert_eq(handle_login_packet(peer, 6), PRESULT_OK);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &type);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &len);
    my_cbuffer_pop_front(&peer->out_buf, id3, sizeof(uuid_t));
    my_cbuffer_pop_front(&peer->out_buf, name3, len - sizeof(uuid_t));
    cr_expect_eq(peer->out_buf.len, 0);
    cr_expect_eq(type, S2C_LOGIN);
    cr_expect_eq(len, 22);
    cr_expect_str_eq(name3, "tables");
    cr_expect_eq(peer->in_buf.len, 0);
    cr_assert_neq(uuid_compare(id, id3), 0);
    server_destroy(&server);
}
