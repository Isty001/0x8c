#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>
#include <form.h>


void create_window(void);

void destroy_window(void);

void form_event(int event);

#endif

