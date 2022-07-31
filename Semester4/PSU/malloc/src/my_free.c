/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_free
*/

#include "my_malloc.h"
#include <unistd.h>

extern list_t *list;

void join_after_free(void)
{
    block_t *current_block = list->first_block;

    while (current_block->next)
        current_block = current_block->next;
    while (current_block->prev && current_block->free)
        current_block = current_block->prev;
    if (!current_block->free) {
        brk(current_block->next);
        current_block->next = NULL;
    } else {
        brk(list);
        list = NULL;
    }
}

void free(void *ptr)
{
    block_t *current_block = list->first_block;

    if (ptr == NULL)
        return;
    while (current_block != NULL) {
        if ((void *)(current_block) + sizeof(*current_block) == (void *)ptr) {
            current_block->free = true;
            break;
        }
        current_block = current_block->next;
    }
    join_after_free();
}
