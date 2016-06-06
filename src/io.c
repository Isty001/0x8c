#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


FILE *open_file(char *path, char *mode)
{
    FILE *file = fopen(path, mode);

    if (NULL == file) {
        //Todo: Error log
        fprintf(stderr, "Failed to open file \"%s\"", path);
        exit(EXIT_FAILURE);
    }
    return file;
}

size_t get_size(FILE *file)
{
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);

    return (size_t)size;
}

char *get_file_content(char *path)
{
    FILE *file = open_file(path, "r");
    size_t size = get_size(file);
    char *buffer = malloc(size);

    fread(buffer, 1, size, file);
    fclose(file);

    return buffer;
}
