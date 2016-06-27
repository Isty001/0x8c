#include <malloc.h>
#include "list.h"


struct list {
    Node *first;
    Node *last;
    TweetType associated_type;
};

static bool is_empty(List *list)
{
    return NULL == list->first;
}

List *create_list(TweetType type)
{
    List *list = alloc(sizeof(List));
    list->associated_type = type;
    list->first = NULL;
    list->last = NULL;

    return list;
}

void destroy_list(List *list)
{
    foreach(list, lambda(LoopCallbackResponse, (Node * current) {
        destroy_tweet(current->tweet);
        free(current);

        return CONTINUE;
    }));

    free(list);
}

static void set_affected_nodes(List *list, Node *node)
{
    if (NULL != node->next) {
        node->next->previous = node;
    }

    if (NULL == list->last) {
        list->last = node;
    }

    list->first = node;
}

static Node *create_node(void)
{
    Node *node = alloc(sizeof(Node));
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

static void prepare_pop(List *list, Node *popped)
{
    if (NULL != popped->previous) {
        popped->previous->next = NULL;
    }
    if (NULL != popped) {
        popped->tweet->contained_by &= ~list->associated_type;
    }
}

static void remove_first_if_also_last(List *list)
{
    if (list->first->tweet->id == list->last->tweet->id) {
        list->first = NULL;
    }
}

Tweet *pop_tweet(List *list)
{
    remove_first_if_also_last(list);

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
        destroy_tweet(tweet);
        return true;
    }
    return false;
}

void foreach(List *list, ForeachCallback callback)
{
    Node *next, *current = list->first;

    if (false == is_empty(list)){
        while (NULL != (next = current->next)) {
            if (BREAK == callback(current)) {
                return;
            }
            current = next;
        }
        callback(current);
    }
}

Tweet *get_first_tweet(List *list)
{
    return list->first->tweet;
}

Tweet *get_last_tweet(List *list)
{
    return list->last->tweet;
}
