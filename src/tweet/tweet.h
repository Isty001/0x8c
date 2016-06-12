#ifndef _0x8c_TWEET_H
#define _0x8c_TWEET_H

#include <stdbool.h>
#include "../misc/tools.h"


typedef enum tweet_type {
    NONE = 1,
    TIMELINE = 2,
    MENTION = 4,
    DIRECT_MESSAGE = 8,
    FAVORITE = 16,
} TweetType;

typedef struct tweet {
    LONGEST_UNSIGNED id;
    char *content;
    char created_at[80];
    LONGEST_UNSIGNED in_reply_to_tweet;
    unsigned int retweet_count;
    unsigned int favorite_count;
    bool is_reply;
    bool is_favorited;
    bool is_retweeted;
    TweetType contained_by;
    LONGEST_UNSIGNED user_id;
    const char *user_name;
} Tweet;

Tweet *create_tweet(char *json_string);

void destroy_tweet(Tweet *tweet);

#endif
