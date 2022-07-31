/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** tests_logout
*/

#include "protocol.h"
#include "server.h"
#include "mock_server.h"
#include "packet_handlers.h"

#include <uuid/uuid.h>
#include <criterion/criterion.h>

Test(logout_packet, not_logged_in)
{
    server_t server;
    peer_t *peer = mock_server(&server);
    mock_generic_packet_t response;

    cr_assert_eq(handle_logout_packet(peer, 0), PRESULT_OK);
    mock_parse_generic(peer, &response);
    cr_expect_eq(peer->out_buf.len, 0);
    cr_expect_eq(response.type, S2C_GENERIC);
    cr_expect_eq(response.code, REPLY_NOT_LOGGED_IN);
    cr_expect_str_eq(response.description, "not logged in");
    server_destroy(&server);
}

Test(logout_packet, extra_data)
{
    server_t server;
    peer_t *peer = mock_server(&server);
    mock_generic_packet_t response;

    mock_log_in(peer, "jack");
    cr_assert_eq(handle_logout_packet(peer, 5), PRESULT_OK);
    mock_parse_generic(peer, &response);
    cr_expect_eq(peer->out_buf.len, 0);
    cr_expect_eq(response.type, S2C_GENERIC);
    cr_expect_eq(response.code, REPLY_INVALID_LENGTH);
    cr_expect_str_eq(response.description, "logout packet should be empty");
    server_destroy(&server);
}

Test(logout_packet, regular)
{
    server_t server;
    peer_t *peer = mock_server(&server);
    uuid_t peer_id;
    uint32_t type;
    uint32_t len;
    uuid_t id;
    char name[MAX_NAME_LENGTH + 1] = {0};

    mock_log_in(peer, "jack");
    uuid_copy(peer_id, peer->user->id);

    cr_assert_eq(handle_logout_packet(peer, 0), PRESULT_OK);

    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &type);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &len);
    my_cbuffer_pop_front(&peer->out_buf, id, sizeof(uuid_t));
    my_cbuffer_pop_front(&peer->out_buf, name, len - sizeof(uuid_t));

    cr_expect_eq(type, S2C_LOGOUT);
    cr_expect_eq(len, 20);
    cr_expect_eq(uuid_compare(id, peer_id), 0);
    cr_expect_str_eq(name, "jack");
    server_destroy(&server);
}
