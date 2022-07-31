/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** nm
*/

#ifndef NM_H_
    #define NM_H_

//MACROS

//NEEDED INCLUDES
    #include <elf.h>
    #include <stdbool.h>

//STRUCTURES
typedef struct nm_s {
    char *content;
    char *filename;
    Elf64_Ehdr *elf;
    Elf64_Shdr *shdr;
    Elf32_Ehdr *elf32;
    Elf32_Shdr *shdr32;
    Elf64_Sym *sym;
    Elf32_Sym *sym32;
    bool is64;
} t_nm;

//PROTOTYPES

/// Process nm on a single file
/// @param filename file to process
/// @returns true in case of error
bool process_single(char const *filename);
/// Process nm on all argv files
/// @param argc argc of execution
/// @param argv argv of execution
/// @returns true in case of error
bool process_all(int argc, char **argv);

char uppercase_if_needed(char c, Elf64_Sym symtab);
Elf64_Sym *sort_symtab(Elf64_Sym *symtab, int size, char *tab);
char get_type(t_nm *meta, int i);
char get_type_next(t_nm *meta, int i);
void print_all(t_nm *meta, char *infotab, int size);
void print_adress(t_nm *meta, int i);
char *create_valid_str(char *original_str);

#endif /* !NM_H_ */
