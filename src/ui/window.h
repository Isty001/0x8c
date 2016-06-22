#ifndef _0x8c_WINDOW_H
#define _0x8c_WINDOW_H

#include <ncurses.h>
#include <form.h>
#include "../tweet/tweet.h"


void create_window(void);

void destroy_window(void);

void form_event(int event);

void add_tweet(Tweet *tweet);

#endif

