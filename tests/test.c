#include "tweet/list_test.h"
#include "misc/io_test.h"
#include "misc/tools_test.h"
#include "tweet/tweet_test.h"

#define NOT_TEST_SUITE

#include "unit_test/minunit_extended.h"


int main(void)
{
    run_list_test_suite();
    run_io_test_suite();
    run_tools_test_suite();
    run_tweet_test_suite();

    clean_up_test_resources();

    return 0;
}
