/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** get_types
*/

#include "nm.h"

char get_type_final(t_nm *meta, int i)
{
    if (meta->shdr[meta->sym[i].st_shndx].sh_flags == SHF_ALLOC + SHF_WRITE)
        return uppercase_if_needed('d', meta->sym[i]);
    if (meta->shdr[meta->sym[i].st_shndx].sh_flags == SHF_ALLOC)
        return uppercase_if_needed('r', meta->sym[i]);
    if (meta->shdr[meta->sym[i].st_shndx].sh_flags == SHF_ALLOC +
    SHF_EXECINSTR)
        return uppercase_if_needed('t', meta->sym[i]);
    return 'z';
}

char get_type_next(t_nm *meta, int i)
{
    char c;
    if (meta->sym[i].st_shndx == SHN_ABS)
        return uppercase_if_needed('a', meta->sym[i]);
    if (meta->shdr[meta->sym[i].st_shndx].sh_type == SHT_NOBITS
        && meta->shdr[meta->sym[i].st_shndx].sh_flags == SHF_ALLOC + SHF_WRITE)
        return uppercase_if_needed('b', meta->sym[i]);
    if (meta->sym[i].st_shndx == SHN_COMMON)
        return uppercase_if_needed('c', meta->sym[i]);
    if (meta->shdr[meta->sym[i].st_shndx].sh_type == SHT_DYNAMIC)
        return uppercase_if_needed('d', meta->sym[i]);
    if (meta->shdr[meta->sym[i].st_shndx].sh_type == SHT_PROGBITS) {
        c = get_type_final(meta, i);
        if (c != 'z')
            return c;
    }
    return uppercase_if_needed('t', meta->sym[i]);
}

char get_type(t_nm *meta, int i)
{
    char c = 0;

    if (ELF64_ST_BIND(meta->sym[i].st_info) == STB_WEAK) {
        c = 'W';
        if (ELF64_ST_TYPE(meta->sym[i].st_info) == STT_OBJECT)
            c = 'V';
        if (meta->sym[i].st_shndx == SHN_UNDEF)
            c += 32;
        return c;
    }
    if (meta->sym[i].st_shndx == SHN_UNDEF ||
    ELF64_ST_BIND(meta->sym[i].st_info) == STB_GNU_UNIQUE)
        return uppercase_if_needed('u', meta->sym[i]);
    return get_type_next(meta, i);
}
