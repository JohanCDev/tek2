/*
** EPITECH PROJECT, 2022
** MyTeams
** File description:
** tests_get_teams
*/

#include "items/team.h"
#include "protocol.h"
#include "server.h"
#include "mock_server.h"
#include "packet_handlers.h"

#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>
#include <criterion/criterion.h>

Test(get_teams_packet, not_logged_in)
{
    server_t server;
    peer_t *peer = mock_server(&server);
    mock_generic_packet_t response;

    cr_assert_eq(handle_get_teams_packet(peer, 0), PRESULT_OK);
    mock_parse_generic(peer, &response);
    cr_expect_eq(peer->out_buf.len, 0);
    cr_expect_eq(response.type, S2C_GENERIC);
    cr_expect_eq(response.code, REPLY_NOT_LOGGED_IN);
    cr_expect_str_eq(response.description, "not logged in");
    server_destroy(&server);
}

Test(get_teams_packet, invalid)
{
    server_t server;
    peer_t *peer = mock_server(&server);
    mock_generic_packet_t response;

    mock_log_in(peer, "jack");
    cr_assert_eq(handle_get_teams_packet(peer, 2), PRESULT_OK);
    mock_parse_generic(peer, &response);
    cr_expect_eq(peer->out_buf.len, 0);
    cr_expect_eq(response.type, S2C_GENERIC);
    cr_expect_eq(response.code, REPLY_INVALID_LENGTH);
    cr_expect_str_eq(
        response.description, "team list packet should be empty");
    server_destroy(&server);
}

Test(get_teams_packet, no_teams)
{
    server_t server;
    peer_t *peer = mock_server(&server);
    uint32_t id;
    uint32_t len;
    uint32_t team_count;

    mock_log_in(peer, "jack");
    cr_assert_eq(handle_get_teams_packet(peer, 0), PRESULT_OK);

    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &id);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &len);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &team_count);

    cr_assert_eq(id, S2C_TEAM_LIST);
    cr_assert_eq(len, 1);
    cr_assert_eq(team_count, 0);
    cr_assert_eq(peer->out_buf.len, 0);
    server_destroy(&server);
}

Test(get_teams_packet, regular)
{
    server_t server;
    peer_t *peer = mock_server(&server);
    team_t *team1 = calloc(sizeof(*team1), 1);
    team_t *team2 = calloc(sizeof(*team2), 1);
    uint32_t id;
    uint32_t len;
    uint32_t team_count;
    uint32_t name_length;
    uint32_t desc_length;
    team_t team;

    uuid_generate(team2->header.id);
    strcpy(team2->name, "My Second Team");
    strcpy(team2->desc, "*the web3 of teams*");
    LIST_INSERT_HEAD(&server.teams, team2, teams);

    uuid_generate(team1->header.id);
    strcpy(team1->name, "My Team");
    strcpy(team1->desc, "A testing team");
    LIST_INSERT_HEAD(&server.teams, team1, teams);

    mock_log_in(peer, "jack");
    cr_assert_eq(handle_get_teams_packet(peer, 0), PRESULT_OK);

    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &id);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &len);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &team_count);

    cr_assert_eq(id, S2C_TEAM_LIST);
    cr_assert_eq(team_count, 2);

    my_cbuffer_pop_front(&peer->out_buf, team.header.id, sizeof(uuid_t));
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &name_length);
    memset(team.name, 0, MAX_NAME_LENGTH + 1);
    my_cbuffer_pop_front(&peer->out_buf, team.name, name_length);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &desc_length);
    memset(team.desc, 0, MAX_DESCRIPTION_LENGTH + 1);
    my_cbuffer_pop_front(&peer->out_buf, team.desc, desc_length);

    cr_expect_eq(uuid_compare(team.header.id, team1->header.id), 0);
    cr_expect_str_eq(team.name, "My Team");
    cr_expect_str_eq(team.desc, "A testing team");

    my_cbuffer_pop_front(&peer->out_buf, team.header.id, sizeof(uuid_t));
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &name_length);
    memset(team.name, 0, MAX_NAME_LENGTH + 1);
    my_cbuffer_pop_front(&peer->out_buf, team.name, name_length);
    my_cbuffer_pop_front_uleb128_32(&peer->out_buf, &desc_length);
    memset(team.desc, 0, MAX_DESCRIPTION_LENGTH + 1);
    my_cbuffer_pop_front(&peer->out_buf, team.desc, desc_length);

    cr_expect_eq(uuid_compare(team.header.id, team2->header.id), 0);
    cr_expect_str_eq(team.name, "My Second Team");
    cr_expect_str_eq(team.desc, "*the web3 of teams*");

    cr_expect_eq(peer->out_buf.len, 0);
    server_destroy(&server);
}
