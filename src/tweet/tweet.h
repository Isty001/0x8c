#ifndef _0x8c_TWEET_H
#define _0x8c_TWEET_H

#include <stdbool.h>
#include <stdint.h>
#include "../misc/utils.h"


typedef enum {
    NONE = 1,
    TIMELINE = 2,
    MENTION = 4,
    DIRECT_MESSAGE = 8,
    FAVORITE = 16,
} TweetType;

typedef struct {
    uint64_t id;
    char *content;
    char created_at[80];
    uint64_t in_reply_to_tweet;
    uint32_t retweet_count;
    uint32_t favorite_count;
    bool is_reply;
    bool is_favorited;
    bool is_retweeted;
    TweetType contained_by;
    uint64_t user_id;
    const char *user_name;
} Tweet;

Tweet *create_tweet(char *json_string);

void destroy_tweet(Tweet *tweet);

#endif
