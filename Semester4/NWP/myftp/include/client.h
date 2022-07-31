/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** client
*/

#pragma once

#include <stdbool.h>
#include "server.h"
typedef enum log_e {
    NO_ST,
    USER_ST,
    ANO_ST,
    LOGGED_ST,
    DISC_ST,
} log_t;

typedef struct s_client {
    log_t log;
    int cli_fd;
    char *path;
} client_t;

/**
* @brief Execute client command
*
* @param client client to execute
* @return int -1 if an error occured
*/
int execute(client_t *client);

/**
* @brief Find a node from the fd characteristic
*
* @param fd fd to find
* @param list list where to find
* @return node_t* node of the client if found, NULL otherwise
*/
node_t *find_by_fd(int fd, linked_list_t *list);

/**
* @brief Create a client node object
*
* @param serv server structure
* @param path path to the wanted directory
* @return node_t* node of the client if created, NULL otherwise
*/
node_t *create_client_node(serv_t *serv, char const *path);
