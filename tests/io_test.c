#include <linux/limits.h>
#include <memory.h>
#include <malloc.h>
#include "io_test.h"
#include "minunit.h"
#include "../src/io.h"


static char *fixtures_dir;

void set_fixtures_dir(void)
{
    fixtures_dir = malloc(PATH_MAX);
    getcwd(fixtures_dir, PATH_MAX);
    strcat(fixtures_dir, "/tests/fixtures/");
}

void io_setup(void)
{
    set_fixtures_dir();
}

void io_tear_down(void)
{
    free(fixtures_dir);
}

void test_get_file_content(void)
{
    char *actual, *expected = "Hello!\n";
    char *path = strcat(fixtures_dir, "test.txt");

    mu_assert(0 == strcmp(expected, actual = get_file_content(path)) ,"Expected and the actual file contents does not match.");

    free(actual);
}

MU_TEST_SUITE(io_test_suite)
{
    MU_RUN_TEST(test_get_file_content);
}

void run_io_test_suite(void)
{
    puts("IO Test Suite: \n");

    MU_SUITE_CONFIGURE(&io_setup, &io_tear_down);
    MU_RUN_SUITE(io_test_suite);
    MU_REPORT();
}
