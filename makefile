CC = clang
CFLAGS = -lncurses -lm -O3 -I./include/
SOURCES = ./src/*.c

all: skfantasy run clean

skfantasy:
	$(CC) $(SOURCES) $(CFLAGS) -o skfantasy

run:
	./skfantasy

clean:
	rm skfantasy
