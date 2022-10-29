CC = clang
WINCC = i686-w64-mingw32-clang
CFLAGS = -lncurses -lm -O3 -I./include/
WINCFLAGS = -lpdcurses -lm -O3 -I./include/
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
