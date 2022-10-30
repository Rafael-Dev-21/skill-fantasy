CC = clang
WINCC = i686-w64-mingw32-clang
CFLAGS = -lncurses -lm -O3 -I./include/ -Wall -Werror -pedantic -g
WINCFLAGS = -lpdcurses -lm -O3 -I./include/ -Wall -Werror -pedantic
SOURCES = ./src/*.c

all: skfantasy run clean

skfantasy:
	$(CC) $(SOURCES) $(CFLAGS) -o skfantasy

exe:
	$(WINCC) $(SOURCES) $(WINCFLAGS) -o skfantasy

run:
	./skfantasy

clean:
	rm skfantasy
