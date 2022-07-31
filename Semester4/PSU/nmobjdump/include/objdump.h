/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** Objdump
*/

#ifndef OBJDUMP_H_
    #define OBJDUMP_H_

// MACROS

// NEEDED INCLUDES
    #include <elf.h>
    #include <stdbool.h>

// STRUCTURES
typedef struct objd_s {
    char *content;
    char *filename;
    Elf64_Ehdr *elf;
    Elf64_Shdr *shdr;
    Elf32_Ehdr *elf32;
    Elf32_Shdr *shdr32;
    bool is64;
} t_objd;

// PROTOTYPES

/// Process nm on a single file
/// @param filename file to process
/// @returns true in case of error
bool process_single(char const *filename);
/// Process nm on all argv files
/// @param argv argv to execute
/// @returns true in case of error
bool process_all(char **argv);
void show_file_info_64(t_objd *metadata, char const *tabinfo);
void show_file_info_32(t_objd *metadata, char const *tabinfo);

/// Get the address of flags in file
/// @param elf elf structure
/// @param shdr headers structure
/// @returns address where flags are located
int get_flags_address_64(Elf64_Ehdr *elf, Elf64_Shdr *shdr);
int get_flags_address_32(Elf32_Ehdr *elf, Elf32_Shdr *shdr);

/// Check if char is valid
/// @param c char to verify
/// @returns 1 if correct
int check_char_valid(char c);

/// Print a ssection of elf file
/// @param tabinfo tab of the section to print
/// @param data file content
/// @param shdr header structure
/// @param i section index
/// @returns false if needing a new line after
bool print_a_sec_64(char const *tabinfo, void *data, Elf64_Shdr *shdr, int i);
bool print_a_sec_32(char const *tabinfo, void *data, Elf32_Shdr *shdr, int i);

/// Show all the sections
/// @param metadata main structure
/// @param tabinfo tab with all the sections
void show_sections_64(t_objd *metadata, char const *tabinfo);
void show_sections_32(t_objd *metadata, char const *tabinfo);

bool show_ascii_values_64(uint32_t *oct, void *data, Elf64_Shdr *shdr, int i);
bool show_ascii_values_32(uint32_t *oct, void *data, Elf32_Shdr *shdr, int i);
void print_spaces(int i);
void show_value_char(void *data, uint32_t size);

#endif /* !OBJDUMP_H_ */
