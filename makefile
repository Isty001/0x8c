SOURCES = $(shell find src -name '*.c' )

#Todo: refakt
TEST_SOURCES = $(shell find src tests -name '*.c' ! -name window.c ! -name window_event.c ! -name curl.c ! -name main.c ! -name display.c)

OBJ = 0x8c.o
DEBUG_FLAG = -D DEBUG
override CFLAGS +=  -l curl -l oauth -l form -l ncurses
TEST_CFLAGS = -D UNIT_TEST $(DEBUG_FLAG)

compile = gcc $1 -g -Wall -Wextra -std=gnu11 -l json-c -o $(OBJ)

default:
	$(call compile,$(SOURCES) $(CFLAGS),twitter)

run:
	make && ./$(OBJ)

run-debug:
	make run CFLAGS="$(DEBUG_FLAG)"

test:
	$(call compile,$(TEST_SOURCES) $(TEST_CFLAGS)) && ./$(OBJ)
