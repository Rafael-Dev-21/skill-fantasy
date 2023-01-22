CC = gcc
CFLAGS = -lncurses -ltinfo -Wall -Wextra -Werror -std=c2x -DUSE_NCURSES
SOURCES = ./src/*.c
MODE = release

ifeq ($(MODE),release)
	CFLAGS += -O2
else ifeq ($(MODE),debug)
	CFLAGS += -g -Og -fsanitize=address,undefined -DDEBUG
endif

all: skfantasy run clean

skfantasy:
	$(CC) $(SOURCES) $(CFLAGS) -o skfantasy

run:
	./skfantasy


package: skfantasy
	tar -czf skfantasy-linux.tar.gz skfantasy
	rm -rf skfantasy

docs: clean
	doxygen Doxyfile

clean:
	rm -rf skfantasy docs
