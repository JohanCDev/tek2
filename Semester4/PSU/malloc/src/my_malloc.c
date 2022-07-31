/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_malloc
*/

#include "my_malloc.h"
#include <unistd.h>

list_t *list;

void create_first_block(block_t *new_section)
{
    list = sbrk(sizeof(list_t));
    if (list == SBRKERROR)
        return;
    new_section->prev = NULL;
    new_section->next = NULL;
    list->first_block = new_section;
}

void create_block(block_t *new_section)
{
    block_t *first = list->first_block;
    while (first->next)
        first = first->next;
    new_section->prev = first;
    new_section->next = NULL;
    first->next = new_section;
}

void insert_section_in_list(block_t *new_section)
{
    new_section->free = false;
    if (!list)
        create_first_block(new_section);
    else
        create_block(new_section);
}

void *search_place(size_t size)
{
    if (list) {
        block_t *current_block = list->first_block;
        return find_free_block(current_block, size);
    }
    return NULL;
}

void *malloc(size_t size)
{
    block_t *new_block = NULL;
    void *address = NULL;
    size_t page_size = getpagesize();

    if (!size)
        return (NULL);
    size = align(size);
    size = (size - 1) / (page_size * 2) * (page_size * 2) + (page_size * 2);
    address = search_place(size);
    if (address)
        return (address);
    if ((new_block = sbrk(sizeof(block_t))) == SBRKERROR)
        return (NULL);
    if ((new_block->data_block = sbrk(size)) == SBRKERROR)
        return (NULL);
    new_block->block_size = size;
    insert_section_in_list(new_block);
    return (new_block->data_block);
}
