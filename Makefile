CC = gcc
CFLAGS = -lncurses -ltinfo -Wall -Wextra -Werror -pedantic -std=c2x -g
SOURCES = ./src/*.c

all: skfantasy run clean

skfantasy:
	$(CC) $(SOURCES) $(CFLAGS) -o skfantasy

run:
	./skfantasy


package: skfantasy
	tar -czf skfantasy-linux.tar.gz skfantasy
	rm -rf skfantasy

docs:
	doxygen Doxyfile

clean:
	rm -rf skfantasy docs
