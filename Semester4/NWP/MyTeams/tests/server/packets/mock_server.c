/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** mock_server
*/

#include "mock_server.h"
#include "cbuffer.h"
#include "peer.h"
#include "server.h"
#include "packet_handlers.h"

#include <string.h>
#include <uuid/uuid.h>

/// Creates a fake instance of the server with one peer.
peer_t *mock_server(server_t *server)
{
    peer_t *peer;

    server_init(server, 0);
    peer = peer_create(-1, NULL);
    peer->server = server;
    LIST_INSERT_HEAD(&server->peers, peer, peers);
    return peer;
}

/// Logs the user in
void mock_log_in(peer_t *peer, char const *name)
{
    size_t name_len = strlen(name);

    my_cbuffer_init(&peer->in_buf, peer->raw_in_buf, PEER_BUFFER_SIZE);
    my_cbuffer_push_back(&peer->in_buf, name, name_len);
    handle_login_packet(peer, name_len);
    my_cbuffer_init(&peer->out_buf, peer->raw_out_buf, PEER_BUFFER_SIZE);
}

void mock_parse_generic(peer_t *peer, mock_generic_packet_t *packet)
{
    size_t code_size;

    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &packet->type);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &packet->len);
    code_size = peer->out_buf.len;
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &packet->code);
    code_size -= peer->out_buf.len;
    memset(packet->description, 0, sizeof(packet->description));
    my_cbuffer_pop_front(
        &peer->out_buf, packet->description, packet->len - code_size);
}
