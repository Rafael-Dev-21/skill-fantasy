CC=clang
CFLAGS=-g -Wall -Werror -pedantic -Iinclude -lncurses -lm
SRCS=src/*.c

all: skfantasy run clean

skfantasy:
	$(CC) $(CFLAGS) $(SRCS) -o skfantasy

run:
	./skfantasy

clean:
	rm skfantasy
