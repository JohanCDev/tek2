/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** is_elf
*/

#include <string.h>
#include <unistd.h>
#include "my.h"

bool is_elf(Elf64_Ehdr *elf)
{
    if (!(elf->e_ident[0] == ELFMAG0 &&
    elf->e_ident[1] == ELFMAG1 &&
    elf->e_ident[2] == ELFMAG2 &&
    elf->e_ident[3] == ELFMAG3 &&
    (elf->e_ident[4] == ELFCLASS32 ||
    elf->e_ident[4] == ELFCLASS64) &&
    elf->e_ident[5] != EV_NONE)) {
        return (bool)my_put_error("Bad file format\n", 0);
    }
    return true;
}
