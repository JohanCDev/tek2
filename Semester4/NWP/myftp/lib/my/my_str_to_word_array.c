/*
** EPITECH PROJECT, 2021
** B-CPE-210-NAN-2-1-stumper5-quentin.leroueil
** File description:
** my_str_to_word_array
*/

#include <stdlib.h>
#include <string.h>

void my_free_array(char **array);

char **my_str_to_word_array(char const *str, char *delims)
{
    char **array = malloc(sizeof(char *));
    char *token = strtok((char *)str, delims);
    int i = 0;

    if (array == NULL)
        return NULL;
    if (str == NULL || delims == NULL) {
        my_free_array(array);
        return NULL;
    }
    while (token != NULL) {
        array[i++] = strdup(token);
        if (array[i - 1] == NULL) {
            my_free_array(array);
            return NULL;
        }
        array = realloc(array, (i + 1) * sizeof(char *));
        token = strtok(NULL, delims);
    }
    return array;
}
