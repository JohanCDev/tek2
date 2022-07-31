/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** modify_string
*/

#include "nm.h"
#include <stdlib.h>
#include <string.h>

char uppercase_if_needed(char c, Elf64_Sym symtab)
{
    if (ELF64_ST_BIND(symtab.st_info) != STB_LOCAL)
        c -= 32;
    return c;
}

bool is_valid_char(char c)
{
    return (c != '.' && c != '_' && c != '@');
}

char *create_valid_str(char *original_str)
{
    char *val_str = malloc(sizeof(char) * (strlen(original_str) + 1));
    int i = 0;

    if (val_str == NULL)
        exit(84);
    for (int j = 0; original_str[j] != '\0'; j++)
        if (is_valid_char(original_str[j])) {
            val_str[i++] = (original_str[j] >= 'A' && original_str[j] <= 'Z' ?
            original_str[j] + 32 : original_str[j]);
        }
    val_str[i] = '\0';
    return val_str;
}
