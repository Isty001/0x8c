#include <malloc.h>
#include <json-c/json.h>
#include <time.h>
#include <memory.h>
#include "tweet.h"


#define JSON struct json_object
#define get_string(json, key) json_object_get_string(move_to_key(json, key))
#define get_int(json, key) json_object_get_int(move_to_key(json, key))
#define get_unsigned(json, key) (unsigned int)get_int(json, key)
#define get_bool(json, key) (bool)json_object_get_boolean(move_to_key(json, key))


static const char *date_format = "%a %b %d %Y - %H:%M";

static Tweet *new_tweet(void)
{
    Tweet *tweet = malloc(sizeof(Tweet));
    tweet->contained_by = NONE;

    return tweet;
}

static JSON *move_to_key(JSON *json, char *key)
{
    JSON *buffer;

    json_object_object_get_ex(json, key, &buffer);

    return buffer;
}

static inline uint64_t get_unsigned_long(JSON *json, char *key)
{
    if (false == json_object_is_type(move_to_key(json, key), json_type_null)) {
        return (uint64_t) strtoll(get_string(json, key), NULL, 0);
    }
    return 0;
}

static void set_content(JSON *json, Tweet *tweet)
{
    const char *content = get_string(json, "text");
    size_t size = strlen(content);

    tweet->content = alloc(size);
    memcpy(tweet->content, content, size);
}

static void set_created_at(JSON *json, Tweet *tweet)
{
    uint64_t timestamp_ms = get_unsigned_long(json, "timestamp_ms");
    time_t time = (time_t)(timestamp_ms / 1000);
    struct tm info;

    localtime_r(&time, &info);
    strftime(tweet->created_at, sizeof(tweet->created_at), date_format, &info);
}

static void build_tweet(JSON *json, Tweet *tweet)
{
    tweet->id = get_unsigned_long(json, "id");
    tweet->in_reply_to_tweet = get_unsigned_long(json, "in_reply_to_status_id");
    tweet->is_reply = tweet->in_reply_to_tweet != 0;
    tweet->favorite_count = get_unsigned(json, "favorite_count");
    tweet->retweet_count = get_unsigned(json, "retweet_count");
    tweet->is_favorited = get_bool(json, "favorited");
    tweet->is_retweeted = get_bool(json, "retweeted");

    set_content(json, tweet);
    set_created_at(json, tweet);
}

static void add_user_data(JSON *json, Tweet *tweet)
{
    JSON *user = move_to_key(json, "user");

    tweet->user_id = get_unsigned_long(user, "id");
    tweet->user_name = get_string(user, "screen_name");
}

//Todo: array of tweet
Tweet *create_tweet(char *json_string)
{
    JSON *json = json_tokener_parse(json_string);
    Tweet *tweet = new_tweet();

    build_tweet(json, tweet);
    add_user_data(json, tweet);

    json_object_put(json);

    return tweet;
}

void destroy_tweet(Tweet *tweet)
{
    //Todo: destroy the tweet properly
    free_multiple(2, tweet->content, tweet);
}
