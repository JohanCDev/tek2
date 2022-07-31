/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** sort
*/

#include "nm.h"
#include <stdlib.h>
#include <string.h>

void swap_if_needed(char *str1, char *str2, Elf64_Sym *sorted, char *tab)
{
    if (strcmp(str1, str2) > 0 || (strcmp(str1, str2) == 0 &&
    strlen(tab + sorted[1].st_name) > strlen(tab + sorted[0].st_name))) {
        Elf64_Sym temp = sorted[1];
        sorted[1] = sorted[0];
        sorted[0] = temp;
    }
}

Elf64_Sym *sort_symtab(Elf64_Sym *symtab, int size, char *tab)
{
    Elf64_Sym *sorted_array = malloc(sizeof(Elf64_Sym) * size);
    char *first_seg_name;
    char *sec_seg_name;

    if (sorted_array == NULL)
        exit(84);
    for (int i = 0; i < size; i++)
        sorted_array[i] = symtab[i];
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size - i - 1; j++) {
            first_seg_name = create_valid_str(tab + sorted_array[j].st_name);
            sec_seg_name = create_valid_str(tab + sorted_array[j + 1].st_name);
            swap_if_needed(first_seg_name, sec_seg_name, &sorted_array[j], tab);
            free(first_seg_name);
            free(sec_seg_name);
        }
    return sorted_array;
}
