#include <memory.h>
#include <stdarg.h>
#include "tools.h"


static size_t get_next_chunk_size(int length, size_t chunk_size)
{
    size_t remaining = length - chunk_size;

    if (remaining > chunk_size) {
        return chunk_size;
    }
    return remaining;
}

void string_chunk(char *string, size_t chunk_size, LoopCallbackResponse (*callback)(char *chunk))
{
    int offset = 0 - chunk_size;
    int length = strlen(string);
    char chunk[chunk_size];
    size_t next_chunk_size;

    while ((offset += chunk_size) < length) {
        memcpy(chunk, &string[offset], next_chunk_size = get_next_chunk_size(length, chunk_size));
        chunk[next_chunk_size] = '\0';

        if (BREAK == callback(chunk)) {
            break;
        }
    }
}

void free_multiple(int count, ...)
{
    va_list items;
    va_start(items, count);

    for (int i = 0; i < count; i++) {
        free(va_arg(items, void *));
    }
    va_end(items);
}
