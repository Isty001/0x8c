#include <assert.h>
#include "window.h"
#include "display.h"

static FORM *form;
static FIELD *fields[2];
static WINDOW *main_window, *form_window, *timeline_window, *notification_window;
static int height;
static int width;

#define PADDING 2
#define FORM_HEIGHT 3
#define FORM_WIDTH width - (2 * PADDING)
#define STREAM_HEIGHT height - (FORM_HEIGHT + PADDING)
#define STREAM_WIDTH (width / 2) - (2 * PADDING)

static void create_main_window(void)
{
    initscr();
    start_color();
    use_default_colors();
    display_init();
    getmaxyx(stdscr, height, width);

    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    main_window = newwin(height, width, 0, 0);
    assert(NULL != main_window);
}

static WINDOW *create_sub_window(int height, int width, int y, int x)
{
    WINDOW *sub_window = derwin(main_window, height, width, y, x);
    assert(NULL != sub_window);

    return sub_window;
}

static void create_form_window(void)
{
    form_window = create_sub_window(FORM_HEIGHT, FORM_WIDTH, height - 4, PADDING);

    box(form_window, 0, 0);
}

static void create_stream_windows(void)
{
    timeline_window = create_sub_window(STREAM_HEIGHT, STREAM_WIDTH, 1, PADDING);
    notification_window = create_sub_window(STREAM_HEIGHT, STREAM_WIDTH, 1, (width / 2) + PADDING);

    mvwvline(main_window, PADDING, width / 2, '|', STREAM_HEIGHT - PADDING);

#ifdef DEBUG
    box(notification_window, 0, 0);
    box(timeline_window, 0, 0);
#endif
}

static void create_form(void)
{
    fields[0] = new_field(2, width - 2, height - 3, 2, 0, 0);
    assert(NULL != fields[0]);

    set_field_opts(fields[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    form = new_form(fields);
    assert(NULL != form);

    set_form_win(form, form_window);
    post_form(form);
}

static void refresh_all(void)
{
    refresh();
    wrefresh(main_window);
    wrefresh(form_window);
    wrefresh(notification_window);
    wrefresh(timeline_window);
    pos_form_cursor(form);
}

void create_window(void)
{
    create_main_window();
    create_form_window();
    vline(0, width / 2);
    create_stream_windows();
    create_form();
    refresh_all();
}

void destroy_window(void)
{
    unpost_form(form);
    free_form(form);
    free_field(fields[0]);
    delwin(form_window);
    delwin(timeline_window);
    delwin(notification_window);
    delwin(main_window);
    endwin();
}

void add_tweet(Tweet *tweet)
{
    display_setup_current(timeline_window, tweet);

    display_head();
    display_content();
    display_info();

    wrefresh(timeline_window);
    refresh();
}

void form_event(int event)
{
    form_driver(form, event);
}
