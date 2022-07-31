#include "ikea.h"

#include <string.h>

static char const *TYPES[] = {
    "chair",
    "table",
    "bed",
    NULL
};

static char const *NAMES[] = {
    "STIG",
    "LÄTT",
    "BJÖRKSNÄS",
    NULL
};

char const *get_furniture(char const *type)
{
    for (unsigned int i = 0; TYPES[i]; ++i)
        if (strcmp(type, TYPES[i]) == 0)
            return NAMES[i];
    return NULL;
}