#ifndef _0x8c_MINUNIT_EXTENDED_H
#define _0x8c_MINUNIT_EXTENDED_H

#ifndef NOT_TEST_SUITE

#include "minunit.h"
#include <string.h>

#define mu_assert_string(expected, actual) MU__SAFE_BLOCK(\
    mu_assert(0 == strcmp(expected, actual), "String does not match expected value"); \
)

#endif

char *read_fixture(char *fixture);

void clean_up_test_resources(void);

#endif
