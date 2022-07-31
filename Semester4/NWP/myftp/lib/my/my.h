/*
** EPITECH PROJECT, 2020
** include my.h
** File description:
** desc
*/

#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

/**
* @brief print an error message and return a value
*
* @param message to print
* @param code to return
* @param fd to print on
* @return int code given
*/
int my_put_error(char *message, int code, FILE *fd);
/**
* @brief print an error message and return a pointer
*
* @param message to print
* @param code to return
* @param fd to print on
* @return void* code given
*/
void *my_put_error_ret_ptr(char *message, void *code, FILE *fd);
/// Turns a string into an array
/// @param str The string to put into an array
/// @param delim Delimitators that will cut the string
/// @returns The array that represents the string cut by the delimitators
/// @since 0.0.0
char **my_str_to_word_array(const char *str, char *delims);
/// Free an array of char **
/// @param array Array to free
/// @since 0.0.0
void my_free_array(char **array);
/**
* @brief Get the length of an array of strings
*
* @param array array to get the length
* @return size_t length
*/
size_t get_arraylen(char const **array);
