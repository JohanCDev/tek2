/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** tests_get_messages
*/

#include "items/message.h"
#include "protocol.h"
#include "server.h"
#include "mock_server.h"
#include "packet_handlers.h"
#include "uuid_util.h"

#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>
#include <criterion/criterion.h>

static void add_messages_to(peer_t *peer, uuid_t recipient_id)
{
    message_list_t messages;
    message_t *message = calloc(sizeof(*message), 1);
    uuid_pair_t key;

    LIST_INIT(&messages);
    uuid_copy(message->author, recipient_id);
    message->timestamp = 1654179747;
    strcpy(message->body, "A test? Dude, no way!");
    LIST_INSERT_HEAD(&messages, message, messages);
    message = calloc(sizeof(*message), 1);
    uuid_copy(message->author, peer->user->id);
    message->timestamp = 1654179512;
    strcpy(message->body, "Hello, this is a test");
    LIST_INSERT_HEAD(&messages, message, messages);

    uuid_pair_init(&key, peer->user->id, recipient_id);
    my_hash_map_insert(&peer->server->messages, &key, &messages);
}

Test(get_messages_packet, not_logged_in)
{
    server_t server;
    peer_t *peer = mock_server(&server);
    mock_generic_packet_t response;

    cr_assert_eq(handle_get_messages_packet(peer, 0), PRESULT_OK);
    mock_parse_generic(peer, &response);
    cr_expect_eq(peer->out_buf.len, 0);
    cr_expect_eq(response.type, S2C_GENERIC);
    cr_expect_eq(response.code, REPLY_NOT_LOGGED_IN);
    cr_expect_str_eq(response.description, "not logged in");
    server_destroy(&server);
}

Test(get_messages_packet, invalid)
{
    server_t server;
    peer_t *peer = mock_server(&server);
    mock_generic_packet_t response;

    mock_log_in(peer, "jack");
    cr_assert_eq(handle_get_messages_packet(peer, 2), PRESULT_OK);
    mock_parse_generic(peer, &response);
    cr_expect_eq(peer->out_buf.len, 0);
    cr_expect_eq(response.type, S2C_GENERIC);
    cr_expect_eq(response.code, REPLY_INVALID_LENGTH);
    cr_expect_str_eq(
        response.description, "get_messages requires a valid uuid");
    server_destroy(&server);
}

Test(get_messages_packet, no_messages)
{
    server_t server;
    peer_t *peer = mock_server(&server);
    uuid_t recipient_id;
    uint32_t id;
    uint32_t len;
    uint32_t message_count;

    mock_log_in(peer, "jack");
    uuid_generate(recipient_id);
    my_cbuffer_push_back(&peer->in_buf, recipient_id, sizeof(uuid_t));
    cr_assert_eq(handle_get_messages_packet(peer, 16), PRESULT_OK);

    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &id);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &len);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &message_count);

    cr_assert_eq(id, S2C_MESSAGE_LIST);
    cr_assert_eq(len, 1);
    cr_assert_eq(message_count, 0);
    cr_assert_eq(peer->out_buf.len, 0);
    server_destroy(&server);
}

Test(get_messages_packet, regular)
{
    server_t server;
    peer_t *peer = mock_server(&server);
    uuid_t recipient_id;
    uint32_t id;
    uint32_t len;
    uint32_t message_count;
    uint32_t body_length;
    message_t message;

    mock_log_in(peer, "jack");
    add_messages_to(peer, recipient_id);
    my_cbuffer_push_back(&peer->in_buf, recipient_id, sizeof(uuid_t));
    cr_assert_eq(handle_get_messages_packet(peer, 16), PRESULT_OK);

    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &id);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &len);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &message_count);

    cr_assert_eq(id, S2C_MESSAGE_LIST);
    cr_assert_eq(message_count, 2);

    my_cbuffer_pop_front(&peer->out_buf, message.author, sizeof(uuid_t));
    my_cbuffer_pop_front_uleb128_64(
        &peer->out_buf, (uint64_t *)&message.timestamp);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &body_length);
    memset(message.body, 0, MAX_BODY_LENGTH + 1);
    my_cbuffer_pop_front(&peer->out_buf, message.body, body_length);

    cr_expect_eq(uuid_compare(message.author, peer->user->id), 0);
    cr_expect_eq(message.timestamp, 1654179512);
    cr_expect_str_eq(message.body, "Hello, this is a test");

    my_cbuffer_pop_front(&peer->out_buf, message.author, sizeof(uuid_t));
    my_cbuffer_pop_front_uleb128_64(
        &peer->out_buf, (uint64_t *)&message.timestamp);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &body_length);
    memset(message.body, 0, MAX_BODY_LENGTH + 1);
    my_cbuffer_pop_front(&peer->out_buf, message.body, body_length);

    cr_expect_eq(uuid_compare(message.author, recipient_id), 0);
    cr_expect_eq(message.timestamp, 1654179747);
    cr_expect_str_eq(message.body, "A test? Dude, no way!");

    cr_expect_eq(peer->out_buf.len, 0);
    server_destroy(&server);
}
