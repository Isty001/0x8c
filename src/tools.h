#ifndef TOOLS_H
#define TOOLS_H

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define check_alloc(pointer)\
 if (NULL == pointer) { \
    perror("Couldn't allocate memory"); exit(EXIT_FAILURE); \
}

#define flag_exists(bitmask, flag) ((bitmask & flag) == flag)

#define lambda(return_type, function_body) ({ return_type __fn__ function_body __fn__; })

#endif
