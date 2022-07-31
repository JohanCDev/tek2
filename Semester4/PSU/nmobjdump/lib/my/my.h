/*
** EPITECH PROJECT, 2020
** include my.h
** File description:
** desc
*/

#ifndef MY_H
    #define MY_H

    #include <stdio.h>
    #include <stdarg.h>
    #include <stdbool.h>
    #include <elf.h>

/// Turns a string into an array
/// @param str The string to put into an array
/// @param delim Delimitators that will cut the string
/// @returns The array that represents the string cut by the delimitators
char **my_str_to_word_array(char *str, char *delims);
/// Opens and read a file
/// @param filepath file to read
/// @returns an allocated char * with file content
char *open_and_read_file(char const *filepath);
/// Print a message on stderr and return an int
/// @param message message to display
/// @param code value to return
/// @returns the value given
int my_put_error(char *message, int code);
/// Print a message on stderr and return a ptr
/// @param message message to display
/// @param code ptr to return
/// @returns the value given
void *my_put_error_ret_ptr(char *message, void *code);
/// Free an array
/// @param array Array to free
void my_free_array(char **array);
/// Check if a file is ELF format
/// @param elf struct elf with infos in it
/// @returns true if file is ELF
bool is_elf(Elf64_Ehdr *elf);

#endif
