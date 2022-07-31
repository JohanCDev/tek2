/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** process
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include "nm.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

void process64(t_nm *meta)
{
    meta->shdr = (Elf64_Shdr *)(meta->content + meta->elf->e_shoff);
    char *infotab = (char *)meta->content +
    meta->shdr[meta->elf->e_shstrndx].sh_offset;
    int size = 0;

    for (int i = 0; i < meta->elf->e_shnum; i++) {
        if (strcmp(&infotab[meta->shdr[i].sh_name], ".symtab") == 0) {
            meta->sym = (void *)meta->elf + (&meta->shdr[i])->sh_offset;
            size = (&meta->shdr[i])->sh_size / (&meta->shdr[i])->sh_entsize;
        } else if (strcmp(&infotab[meta->shdr[i].sh_name], ".strtab") == 0) {
            infotab = (char *)meta->elf + (&meta->shdr[i])->sh_offset;
        }
    }
    meta->sym = sort_symtab(meta->sym, size, infotab);
    print_all(meta, infotab, size);
}

bool process_single(char const *filename)
{
    t_nm metadata;

    metadata.content = open_and_read_file(filename);
    if (metadata.content == NULL)
        return false;
    metadata.elf = (Elf64_Ehdr *) metadata.content;
    if (is_elf(metadata.elf) == false)
        return false;
    metadata.is64 = metadata.elf->e_ident[4] == ELFCLASS32 ? false : true;
    if (metadata.is64)
        process64(&metadata);
    free(metadata.content);
    return true;
}

bool process_all(int argc, char **argv)
{
    bool has_an_error = false;
    for (int i = 1; i < argc; i++) {
        printf("\n%s:\n", argv[i]);
        if (process_single(argv[i]) == false)
            has_an_error = true;
    }
    return has_an_error;
}
