#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef enum tweet_type {
    NONE = 1,
    TIMELINE = 2,
    MENTION = 4,
    DIRECT_MESSAGE = 8,
    FAVORITE = 16,
} TweetType;

typedef enum foreach_state {
    CONTINUE,
    HALT,
} ForeachState;

typedef struct tweet {
    int id;
    TweetType contained_by;
} Tweet;

typedef struct list List;

typedef ForeachState (*ForeachCallback)(Tweet *current);

List *create_list(TweetType associated_type);

Tweet *get_first_tweet(List *list);

Tweet *get_last_tweet(List *list);

void unshift_tweet(List *list, Tweet *tweet);

Tweet *pop_tweet(List *list);

bool free_if_orphaned(Tweet *tweet);

Tweet *create_tweet(void);

void foreach(List *list, ForeachCallback callback);

#endif
