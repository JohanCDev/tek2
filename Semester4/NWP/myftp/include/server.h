/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** server
*/

#pragma once

// NEEDED INCLUDES
#include "linked_list.h"
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>

// MACROS
#define min(a, b) a > b ? b : a
#define max(a, b) a < b ? b : a
#define HELPER_DISPLAY                                                     \
"USAGE: ./myftp port path\n\tport is the port number on which the server " \
"socket listens\n\tpath is the path to the home directory for the "        \
"Anonymous user\n"
#define HELPER_DISPLAYED 2
#define FAILURE_PROGRAM 84
#define STWA_ERR_MESS "Str to word array failed"

// STRUCTURES
typedef struct s_serv {
    int sock;
    struct sockaddr_in serv;
    struct sockaddr_in cli;
    socklen_t cli_len;
    char **commands_name;
    int connfd;
    fd_set curr_sock;
    fd_set read_sock;
    linked_list_t *list;
} serv_t;

// PROTOTYPES

/**
* @brief Process all the program
*
* @param argv args
* @return exit status
*/
int process(int port, char const *path);

/**
* @brief main loop of the server
*
* @param serv server structure
* @return int -1 if there is an error
*/
int loop_server(serv_t *serv, char const *path);

/**
* @brief Handle select return values and fd_sets for the server
*
* @param serv server structure
* @param i fd_set index
* @param path path given at execution
* @return int -1 if there is an error, 1 if new client connected 0 otherwise
*/
int handle_select(serv_t *serv, int i, char const *path);
