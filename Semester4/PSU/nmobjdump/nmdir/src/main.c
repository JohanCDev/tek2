/*
** EPITECH PROJECT, 2022
** nmobjdump
** File description:
** main
*/

#include "my.h"
#include "nm.h"

int main(int argc, char **argv)
{
    switch (argc) {
    case 1:
        return (process_single("a.out") == false ? 0 : 84);
    case 2:
        return (process_single(argv[1]) == false ? 0 : 84);
    default:
        return (process_all(argc, argv) == false ? 0 : 84);
    }
    return 0;
}
