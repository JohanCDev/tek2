/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** print
*/

#include "nm.h"
#include <stdio.h>

void print_adress(t_nm *meta, int i)
{
    if (meta->sym[i].st_size == 0 && meta->sym[i].st_shndx == SHN_UNDEF)
        printf("                ");
    else
        printf("%016lx", meta->sym[i].st_value);
}

void print_all(t_nm *meta, char *infotab, int size)
{
    for (int i = 0; i < size; i++)
        if (meta->sym[i].st_name != SHN_UNDEF &&
        ELF64_ST_TYPE(meta->sym[i].st_info) != STT_FILE) {
            print_adress(meta, i);
            printf(" %c %s\n", get_type(meta, i), infotab +
            meta->sym[i].st_name);
        }
}
