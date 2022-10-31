CC=clang
SOURCES=src/*.c
INCLUDES=-Iinclude
LIBS=-lncurses -lm
CFLAGS=-g -Wall -Werror -pedantic $(INCLUDES) $(LIBS)
BIN=skfantasy
ITEMS=$(BIN)
PACKAGE=skfantasy-linux.zip
RM=rm -rf

all: linux

windows: CC=i686-w64-mingw32-clang
windows: LIBS=-lpdcurses
windows: ITEMS=skfantasy.exe pdcurses.dll
windows: PACKAGE=skfantasy-windows.zip
windows: build package clean


linux: build package clean

build:
	$(CC) $(SOURCES) $(CFLAGS) -o $(BIN)

package:
	zip $(PACKAGE) $(ITEMS)

run: build
	./skfantasy

clean:
	$(RM) skfantasy skfantasy.exe
