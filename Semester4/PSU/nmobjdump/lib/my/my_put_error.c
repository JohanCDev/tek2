/*
** EPITECH PROJECT, 2020
** B-PSU-100-NAN-1-1-myprintf-johan.chrillesen
** File description:
** my_put_error
*/

#include <unistd.h>
#include <string.h>

int my_put_error(char *message, int code)
{
    int len = strlen(message);

    write(2, message, len);
    return (code);
}

void *my_put_error_ret_ptr(char *message, void *code)
{
    write(2, message, strlen(message));
    return (code);
}
