#include "ikea.h"
#include <stdio.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 84


int main(int ac, char **av)
{
    if (ac != 2) {
        fputs("Usage: hello <furniture type>\nCurrently supported furniture types: chair, table, bed\n", stderr);
        return (EXIT_FAILURE);
    }
    printf("Selected furniture type: %s\n", av[1]);
    printf("Ikea corresponding furniture name: %s\n", get_furniture(av[1]));
    return (EXIT_SUCCESS);
}