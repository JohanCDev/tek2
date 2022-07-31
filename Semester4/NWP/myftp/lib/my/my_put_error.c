/*
** EPITECH PROJECT, 2020
** B-PSU-100-NAN-1-1-myprintf-johan.chrillesen
** File description:
** my_put_error
*/

#include <unistd.h>
#include <stdio.h>

int my_put_error(char const *message, int code, FILE *fd)
{
    fprintf(fd, "%s\n", message);
    return (code);
}

void *my_put_error_ret_ptr(char const *message, void *ret, FILE *fd)
{
    fprintf(fd, "%s\n", message);
    return (ret);
}
