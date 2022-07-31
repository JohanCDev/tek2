/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_malloc
*/

#ifndef MY_MALLOC_H_
    #define MY_MALLOC_H_

// MACROS
    #define SBRKERROR (void *)-1
    #define MULNOTOVERFLOW ((size_t)1 << (sizeof(size_t) * 4))
    #define align(x) (((((x)-1) >> 2) << 2) + 4)

// NEEDED INCLUDES
    #include <stdbool.h>
    #include <stddef.h>

// STRUCTURES
typedef struct block_s {
    void *data_block;
    size_t block_size;
    bool free;
    struct block_s *next;
    struct block_s *prev;
} block_t;

typedef struct list_s {
    block_t *first_block;
} list_t;

// PROTOTYPES
void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);
void *reallocarray(void *ptr, size_t nmemb, size_t size);
void *search_place(size_t size);
void *find_free_block(block_t *current_block, size_t size);

#endif/* !MY_MALLOC_H_ */
