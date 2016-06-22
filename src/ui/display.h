#ifndef TWITTER_DISPLAY_H
#define TWITTER_DISPLAY_H


void display_init(void);

void display_head();

void display_content();

void display_info();

void display_setup_current(WINDOW *_window, Tweet *_tweet);

#endif
