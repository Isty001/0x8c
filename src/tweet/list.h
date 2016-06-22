#ifndef _0x8c_LIST_H
#define _0x8c_LIST_H

#include <stdbool.h>
#include "../misc/utils.h"
#include "tweet.h"


typedef struct node {
    struct node *next;
    Tweet *tweet;
    struct node *previous;
} Node;

typedef struct list List;

typedef LoopCallbackResponse (*ForeachCallback)(Node *current);

List *create_list(TweetType associated_type);

void destroy_list(List *list);

Tweet *get_first_tweet(List *list);

Tweet *get_last_tweet(List *list);

void unshift_tweet(List *list, Tweet *tweet);

Tweet *pop_tweet(List *list);

bool free_if_orphaned(Tweet *tweet);

void foreach(List *list, ForeachCallback callback);

#endif
