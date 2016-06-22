#include <ncurses.h>
#include "../tweet/tweet.h"


typedef enum {
    GREEN = 1,
    BLUE = 2,
    WHITE = 3
} Color;

typedef void (*Callback)(void);

static Tweet *tweet;
static WINDOW *window;

#define callback(block) ({ lambda(void, (void){ block }); })

void display_init(void)
{
    init_pair(GREEN, COLOR_GREEN, -1);
    init_pair(BLUE, COLOR_BLUE, -1);
    init_pair(WHITE, COLOR_WHITE, -1);
}

void display_setup_current(WINDOW *_window, Tweet *_tweet)
{
    window = _window;
    tweet = _tweet;
}

void display_colored(Color color, Callback callable)
{
    wattron(window, COLOR_PAIR(color));
    callable();
    wattroff(window, COLOR_PAIR(color));
}

void display_colored_bold(Color color, Callback callable)
{
    wattron(window, A_BOLD);
    display_colored(color, callable);
    wattroff(window, A_BOLD);
}

void display_head(void)
{
    display_colored_bold(GREEN, callback({
            wprintw(window, "%s ", tweet->user_name);
    }));

    display_colored_bold(WHITE, callback({
            wprintw(window, "%s\n\n", tweet->created_at);
    }));
}

void display_content(void)
{
    display_colored(WHITE, callback({
            wprintw(window, "%s\n\n", tweet->content);
    }));
}

void display_info(void)
{
    display_colored_bold(BLUE, callback({
            wprintw(window, "FAV: %d RT: %d \n\n", tweet->retweet_count, tweet->favorite_count);
    }));
}
