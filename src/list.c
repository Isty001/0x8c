#include <malloc.h>
#include "list.h"
#include "tools.h"

typedef struct node Node;

struct node {
    Node *next;
    Tweet *tweet;
    Node *previous;
};

struct list {
    Node *first;
    Node *last;
    TweetType associated_type;
};

List *create_list(TweetType type)
{
    List *list = malloc(sizeof(List));
    list->associated_type = type;
    list->first = NULL;
    list->last = NULL;

    return list;
}

void set_affected_nodes(List *list, Node *node)
{
    if (NULL != node->next) {
        node->next->previous = node;
    }

    if (NULL == list->last) {
        list->last = node;
    }

    list->first = node;
}

Node *create_node(void)
{
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->previous = NULL;

    return node;
}

void unshift_tweet(List *list, Tweet *tweet)
{
    Node *node = create_node();
    node->next = list->first;

    tweet->contained_by |= list->associated_type;
    node->tweet = tweet;

    set_affected_nodes(list, node);
}

void prepare_pop(List *list, Node *popped)
{
    if (NULL != popped->previous) {
        popped->previous->next = NULL;
    }
    if (NULL != popped) {
        popped->tweet->contained_by &= ~list->associated_type;
    }
}

Tweet *pop_tweet(List *list)
{
    Node *popped = list->last;
    Tweet *popped_tweet = popped->tweet;
    list->last = popped->previous;

    prepare_pop(list, popped);
    free(popped);

    return popped_tweet;
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

    return tweet;
}

void foreach(List *list, ForeachCallback callback)
{
    Node *current = list->first;

    while (NULL != current->next) {
        if (HALT == callback(current->tweet)) {
            return;
        }
        current = current->next;
    }
    callback(current->tweet);
}

Tweet *get_first_tweet(List *list)
{
    return list->first->tweet;
}

Tweet *get_last_tweet(List *list)
{
    return list->last->tweet;
}
