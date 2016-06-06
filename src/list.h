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
    struct tweet *next;
    struct tweet *previous;
    TweetType contained_by;
} Tweet;

typedef struct list {
    Tweet *first;
    Tweet *last;
    TweetType associated_type;
} List;

typedef ForeachState (*ForeachCallback)(Tweet *current);

List *create_list(TweetType associated_type);

void unshift_tweet(List *list, Tweet *new);

Tweet *pop_tweet(List *list);

bool free_if_orphaned(Tweet *tweet);

Tweet *create_tweet(void);

void foreach(List *list, ForeachCallback callback);

#endif
