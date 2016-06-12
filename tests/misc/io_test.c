#include <memory.h>
#include <malloc.h>
#include <stdlib.h>
#include "../unit_test/minunit_extended.h"


void test_get_file_content(void)
{
    char *actual, *expected = "Hello!\n";

    mu_assert(0 == strcmp(expected, actual = read_fixture("test.txt")) ,"Expected and the actual file contents does not match.");

    free(actual);
}

MU_TEST_SUITE(io_test_suite)
{
    MU_RUN_TEST(test_get_file_content);
}

void run_io_test_suite(void)
{
    puts("IO Test Suite: \n");

    MU_RUN_SUITE(io_test_suite);
    MU_REPORT();
}
