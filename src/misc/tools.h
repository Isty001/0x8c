#ifndef _0x8c_TOOLS_H
#define _0x8c_TOOLS_H

#include <stdio.h>
#include <stdlib.h>


typedef enum loop_callback_response {
    CONTINUE,
    BREAK,
} LoopCallbackResponse;

#define LONGEST_UNSIGNED unsigned long long int

#define flag_exists(bitmask, flag) ((bitmask & flag) == flag)

#define lambda(return_type, function_body) ({ return_type __fn__ function_body __fn__; })

#define die(message) do { perror(message); exit(EXIT_FAILURE); } while(0)

#define alloc(size) ({ \
    void *pointer = malloc(size); \
    if (NULL == pointer) { \
        die("Couldn't allocate memory"); \
    } \
    pointer; \
})

void string_chunk(char *string, size_t chunk_size, LoopCallbackResponse (*callback)(char *chunk));

void free_multiple(int count, ...);

#endif
