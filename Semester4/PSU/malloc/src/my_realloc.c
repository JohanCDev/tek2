/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_realloc
*/

#include "my_malloc.h"
#include <string.h>
#include <stdint.h>

extern list_t *list;

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if ((nmemb >= MULNOTOVERFLOW || size >= MULNOTOVERFLOW) && \
    nmemb > 0 && SIZE_MAX / nmemb < size) {
        return NULL;
    }
    return realloc(ptr, size * nmemb);
}

void *realloc(void *ptr, size_t size)
{
    void *new_ptr;

    if (!ptr)
        return malloc(size);
    if (!size) {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;
    memcpy(new_ptr, ptr, size);
    free(ptr);
    return new_ptr;
}
