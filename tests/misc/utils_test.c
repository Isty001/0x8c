#include <memory.h>
#include "../unit_test/minunit_extended.h"
#include "../../src/misc/utils.h"


void safe_assert_string(char *expected, char *actual)
{
    mu_assert_string(expected, actual);
}

MU_TEST(test_string_chunk)
{
    int i = 0;
    char *expected[3] = {"Hell", "o Wo", "rld"};

    string_chunk("Hello World", 4, lambda(LoopCallbackResponse, (char *chunk) {
        safe_assert_string(expected[i++], chunk);

        return CONTINUE;
    }));
}

MU_TEST(test_broken_chunk)
{
    int execution_count = 0;

    string_chunk("Hello World", 1, lambda(LoopCallbackResponse, (char *chunk) {
        safe_assert_string("H", chunk);
        if (execution_count > 0) {
            die("This should be executed only once");
        }
        execution_count++;

        return BREAK;
    }));
}

MU_TEST(test_over_sized_chunk)
{
    string_chunk("Hello World", 30, lambda(LoopCallbackResponse, (char *chunk) {
        safe_assert_string("Hello World", chunk);

        return CONTINUE;
    }));
}

MU_TEST_SUITE(tools_test_suite)
{
    MU_RUN_TEST(test_string_chunk);
    MU_RUN_TEST(test_broken_chunk);
    MU_RUN_TEST(test_over_sized_chunk);
}

void run_tools_test_suite(void)
{
    puts("Tools test suite:\n");

    MU_RUN_SUITE(tools_test_suite);
    MU_REPORT();
}
