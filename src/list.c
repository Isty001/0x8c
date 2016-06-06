#include <malloc.h>
#include "list.h"
#include "tools.h"


List *create_list(TweetType type)
{
    List *list = malloc(sizeof(List));
    list->associated_type = type;
    list->first = NULL;
    list->last = NULL;

    return list;
}

void setup_new(List *list, Tweet *new)
{
    new->contained_by |= list->associated_type;
    new->next = list->first;

    if (NULL != new->next) {
        new->next->previous = new;
    }
}

void unshift_tweet(List *list, Tweet *new)
{
    setup_new(list, new);
    list->first = new;

    if (NULL == list->last) {
        list->last = new;
    }
}

void prepare_pop(List *list, Tweet *popped)
{
    if (NULL != popped->previous) {
        popped->previous->next = NULL;
    }
    if (NULL != popped) {
        popped->contained_by &= ~list->associated_type;
    }
}

Tweet *pop_tweet(List *list)
{
    Tweet *popped = list->last;
    list->last = popped->previous;

    prepare_pop(list, popped);

    return popped;
}

bool free_if_orphaned(Tweet *tweet)
{
    if (tweet->contained_by == NONE) {
        free(tweet);
        return true;
    }
    return false;
}

Tweet *create_tweet(void)
{
    Tweet *tweet = malloc(sizeof(Tweet));
    tweet->contained_by = NONE;
    tweet->next = NULL;
    tweet->previous = NULL;

    return tweet;
}

void foreach(List *list, ForeachCallback callback)
{
    Tweet *current = list->first;

    while (NULL != current->next) {
        if (HALT == callback(current)) {
            return;
        }
        current = current->next;
    }
    callback(current);
}
