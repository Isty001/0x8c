#include <malloc.h>
#include <stdlib.h>
#include "../unit_test/minunit.h"
#include "../../src/tweet/list.h"


List *timeline = NULL, *mention = NULL;
Tweet *first = NULL, *second = NULL, *third = NULL;

Tweet *create_test_tweet(unsigned long long int id)
{
    Tweet *tweet = malloc(sizeof(Tweet));
    tweet->contained_by = NONE;
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
    destroy_list(timeline);
    destroy_list(mention);
}

void assert_first_and_last(void)
{
    mu_assert_int_eq(third->id, get_first_tweet(timeline)->id);
    mu_assert_int_eq(first->id, get_last_tweet(timeline)->id);
}

void assert_popped_tweets(void)
{
    Tweet *third_popped;

    mu_assert_int_eq(first->id, pop_tweet(timeline)->id);
    mu_assert_int_eq(second->id, pop_tweet(timeline)->id);

    third_popped = pop_tweet(timeline);
    mu_assert_int_eq(third->id, third_popped->id);
    mu_assert(free_if_orphaned(third_popped), "Orphaned Tweet is not freed");

    free(first);
    free(second);
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
}

void safe_assert_int(int expected, unsigned long long int actual)
{
    mu_assert_int_eq(expected, actual);
}

MU_TEST(test_foreach)
{
    int id = 3;

    foreach(timeline, lambda(LoopCallbackResponse, (Node * current) {
        safe_assert_int(id--, current->tweet->id);
        return CONTINUE;
    }));
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
