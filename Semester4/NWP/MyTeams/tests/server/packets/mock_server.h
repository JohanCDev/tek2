/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** mock_server
*/

#pragma once

struct peer;
struct server;

#include "protocol.h"

#include <stdint.h>

typedef struct {
    s2c_packet_id_t type;
    uint32_t len;
    reply_code_t code;
    char description[MAX_BODY_LENGTH + 1];
} mock_generic_packet_t;

/// Creates a fake instance of the server with one peer.
struct peer *mock_server(struct server *server);

/// Logs the user in
void mock_log_in(struct peer *peer, char const *name);

/// Parses the next generic packet from the peer.
///
/// @param peer The peer.
/// @param[out] packet Where to store the parsed packet.
void mock_parse_generic(struct peer *peer, mock_generic_packet_t *packet);
