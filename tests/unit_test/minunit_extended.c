#include <stdlib.h>
#include <linux/limits.h>
#include <unistd.h>
#include <memory.h>
#include "../../src/misc/io.h"


static char *fixtures_dir = NULL;

char *get_fixtures_dir(void)
{
    if (NULL == fixtures_dir) {
        fixtures_dir = malloc(PATH_MAX);
        getcwd(fixtures_dir, PATH_MAX);
        strcat(fixtures_dir, "/tests/fixtures/");
    }
    return fixtures_dir;
}

char *read_fixture(char *fixture)
{
    char path[PATH_MAX];
    sprintf(path, "%s/%s", get_fixtures_dir(), fixture);

    return read_file(path);
}

void clean_up_test_resources(void)
{
    free(fixtures_dir);
}
