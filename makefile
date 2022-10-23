CC = clang
CFLAGS = -lncurses -lm -I./include/
SOURCES = ./src/*.c

all: skfantasy run clean

skfantasy:
	$(CC) $(SOURCES) $(CFLAGS) -o skfantasy

run:
	./skfantasy

clean:
	rm skfantasy
