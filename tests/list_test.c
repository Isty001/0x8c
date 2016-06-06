#include <malloc.h>
#include <stdlib.h>
#include <stdarg.h>
#include "minunit.h"
#include "../src/list.h"
#include "../src/tools.h"


List *timeline = NULL, *mention = NULL;
Tweet *first = NULL, *second = NULL, *third = NULL;

void free_tweets(int count, ...)
{
    va_list tweets;
    va_start(tweets, count);

    for (int i = 0; i < count; i++) {
        free(va_arg(tweets, Tweet*));
    }
    va_end(tweets);
}

void free_all_tweets(void)
{
    free_tweets(3, first, second, third);
}

Tweet *create_test_tweet(int id)
{
    Tweet *tweet = create_tweet();
    tweet->id = id;

    return tweet;
}

void unshift_timeline_tweets(void)
{
    unshift_tweet(timeline, first = create_test_tweet(1));
    unshift_tweet(timeline, second = create_test_tweet(2));
    unshift_tweet(timeline, third = create_test_tweet(3));
}

void list_setup(void)
{
    timeline = create_list(TIMELINE);
    mention = create_list(MENTION);
    unshift_timeline_tweets();
}

void list_tear_down(void)
{
    free_tweets(2, timeline, mention);
}

void assert_first_and_last(void)
{
    mu_assert_int_eq(third->id, timeline->first->id);
    mu_assert_int_eq(first->id, timeline->last->id);
}

void assert_popped_tweets(void)
{
    Tweet *third_popped;

    mu_assert_int_eq(first->id, pop_tweet(timeline)->id);
    mu_assert_int_eq(second->id, pop_tweet(timeline)->id);

    third_popped = pop_tweet(timeline);
    mu_assert_int_eq(third->id, third_popped->id);
    mu_assert(free_if_orphaned(third_popped), "Orphaned Tweet is not freed");

    free_tweets(2, first, second);
}

MU_TEST(test_unshift_pop)
{
    assert_first_and_last();
    assert_popped_tweets();
}

void assert_list_flags()
{
    mu_assert(false == flag_exists(first->contained_by, TIMELINE), "Timeline flag sohuldn't be set");
    mu_assert(true == flag_exists(first->contained_by, MENTION), "Mention flag should be set");
}

MU_TEST(test_multiple_list_contained_tweet)
{
    unshift_tweet(mention, first);

    mu_assert_int_eq(NONE | TIMELINE | MENTION, first->contained_by);
    mu_assert(false == free_if_orphaned(pop_tweet(timeline)), "This shouldn't be freed yet");

    assert_list_flags();
    mu_assert(true == free_if_orphaned(pop_tweet(mention)), "This should be freed");

    free_tweets(2, second, third);
}

void safe_assert_int(int expected, int actual)
{
    mu_assert_int_eq(expected, actual);
}

MU_TEST(test_foreach)
{
    int id = 3;

    foreach(timeline, lambda(ForeachState, (Tweet * current) {
        safe_assert_int(id--, current->id);
        return CONTINUE;
    }));

    free_all_tweets();
}

void list_test_suite(void)
{
    MU_RUN_TEST(test_unshift_pop);
    MU_RUN_TEST(test_multiple_list_contained_tweet);
    MU_RUN_TEST(test_foreach);
}


void run_list_test_suite(void)
{
    puts("List Test Suite: \n");

    MU_SUITE_CONFIGURE(&list_setup, &list_tear_down);
    MU_RUN_SUITE(list_test_suite);
    MU_REPORT();
}