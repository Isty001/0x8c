SOURCES = $(shell find src -name '*.c' )
TEST_SOURCES = $(shell find src tests -name '*.c' ! -name window.c ! -name window_event.c ! -name curl.c ! -name main.c )

DEBUG_FLAG = -D DEBUG
COMMON_CFLAGS = -g -Wall -Wextra -l json-c -std=gnu11
override CFLAGS +=  -l curl -l oauth -l form -l ncurses

TEST_CFLAGS = -D UNIT_TEST $(DEBUG_FLAG)

default:
	gcc $(SOURCES) $(CFLAGS) $(COMMON_CFLAGS) -o twitter.o

run:
	make && ./twitter.o

run-debug:
	make run CFLAGS="$(DEBUG_FLAG)"

test:
	gcc $(TEST_SOURCES) $(TEST_CFLAGS) $(COMMON_CFLAGS) -o twitter_test.o && ./twitter_test.o
