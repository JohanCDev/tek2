/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_malloc
*/

#include "my_malloc.h"
#include <string.h>
#include <stdint.h>

extern list_t *list;

void *find_free_block(block_t *current_block, size_t size)
{
    while (current_block->next) {
        if (current_block->free == true && \
        current_block->block_size >= size) {
            current_block->free = false;
            return current_block->data_block;
        }
        current_block = current_block->next;
    }
    return NULL;
}

void *calloc(size_t nmemb, size_t size)
{
    void *ptr;

    if (nmemb == 0 || size == 0 || SIZE_MAX / nmemb < size)
        return NULL;
    ptr = malloc(nmemb * size);
    return memset(ptr, 0, nmemb * size);
}
