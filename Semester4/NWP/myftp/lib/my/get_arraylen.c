/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** get_length_array
*/

#include <stddef.h>

size_t get_arraylen(char const **array)
{
    size_t i = 0;

    while (array[i] != NULL)
        i++;
    return i;
}
