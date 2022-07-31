/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** EXECUTION
*/

#pragma once

#include "client.h"

#define COMMAND_QUIT 1
#define COMMAND_FOUND 2
#define COMMAND_NOT_FOUND 3

/**
* @brief Execute the user command
*
* @param command all command line
* @return -1 if an error occured
*/
int exec_user(client_t *cli, char const **command);

/**
* @brief Execute the password command
*
* @param command all command line
* @return -1 if an error occured
*/
int exec_pass(client_t *cli, char const **command);

/**
* @brief Execute the cwd command
*
* @param command all command line
* @return -1 if an error occured
*/
int exec_cwd(client_t *cli, char const **command);

/**
* @brief Execute the cdup command
*

* @param command all command line
* @return -1 if an error occured
*/
int exec_cdup(client_t *cli, char const **command);

/**
* @brief Execute the quit command
* @param command all command line
* @return -1 if an error occured
*/
int exec_quit(client_t *cli, char const **command);

/**
* @brief Execute the delete command
*
* @param command all command line
* @return -1 if an error occured
*/
int exec_delete(client_t *cli, char const **command);

/**
* @brief Execute the noop command
*
* @param command all command line
* @return -1 if an error occured
*/
int exec_noop(client_t *cli, char const **command);

/**
* @brief Execute the pwd command
*

* @param command all command line
* @return -1 if an error occured
*/
int exec_pwd(client_t *cli, char const **command);

/**
* @brief Execute the pasv command
*
* @param command all command line
* @return -1 if an error occured
*/
int exec_pasv(client_t *cli, char const **command);

/**
* @brief Execute the port command
*
* @param command all command line
* @return -1 if an error occured
*/
int exec_port(client_t *cli, char const **command);

/**
* @brief Execute the help command
*
* @param command all command line
* @return -1 if an error occured
*/
int exec_help(client_t *cli, char const **command);

/**
* @brief Execute the retr command
*
* @param command all command line
* @return -1 if an error occured
*/
int exec_retr(client_t *cli, char const **command);

/**
* @brief Execute the stor command
*
* @param command all command line
* @return -1 if an error occured
*/
int exec_stor(client_t *cli, char const **command);

/**
* @brief Execute the list command
*
* @param command all command line
* @return -1 if an error occured
*/
int exec_list(client_t *cli, char const **command);

/**
* @brief Handle the execution return value
*
* @param found value if a command was found
* @param fd fd of the client
* @return int 1 if quit command and 0 if not
*/
int handle_execution_return(int found, int fd);
