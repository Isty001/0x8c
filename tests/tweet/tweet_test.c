#include <malloc.h>
#include "../unit_test/minunit_extended.h"
#include "../../src/tweet/tweet.h"


MU_TEST(test_create_tweet)
{
    char *json_string = read_fixture("tweet.json");
    Tweet *tweet = create_tweet(json_string);

    mu_assert(false == tweet->is_favorited && tweet->is_retweeted && false == tweet->is_reply, "Boolean values of the tweet are incorrect");
    mu_assert(tweet->favorite_count == 0, "Favorite should be 0");
    mu_assert(tweet->retweet_count == 98, "Retweet count should be 98");
    mu_assert(738428918907080706 == tweet->id, "Invalid id");
    mu_assert(0 == tweet->in_reply_to_tweet && false == tweet->is_reply, "Tweet shouldn't be a reply");
    mu_assert_string("Hello, I'm a test tweet ;_;", tweet->content);
    mu_assert_string("Thu Jun 02 2016 - 19:55", tweet->created_at);

    destroy_tweet(tweet);
    free(json_string);
}

MU_TEST_SUITE(tweet_test_suite)
{
    MU_RUN_TEST(test_create_tweet);
}

void run_tweet_test_suite(void)
{
    puts("Tweet test suite: \n");

    MU_RUN_SUITE(tweet_test_suite);
    MU_REPORT();
}
