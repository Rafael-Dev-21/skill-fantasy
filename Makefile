CC=
SOURCES=src/*.c
INCLUDES=-Iinclude
LIBS=
CFLAGS=-g -Wall -Werror -pedantic $(INCLUDES) $(LIBS)
BIN=skfantasy
ITEMS=
PACKAGE=
RM=rm -rf

all: windows linux

windows: CC=i686-w64-mingw32-clang
windows: LIBS=-lpdcurses
windows: ITEMS=skfantasy.exe pdcurses.dll
windows: PACKAGE=skfantasy-windows.zip
windows: build package clean

linux: CC=clang
linux: LIBS=-lncurses -lm
linux: ITEMS=$(BIN)
linux: PACKAGE=skfantasy-linux.zip
linux: build package clean

build:
	$(CC) $(SOURCES) $(CFLAGS) -o $(BIN)

package:
	zip $(PACKAGE) $(ITEMS)

clean:
	$(RM) skfantasy skfantasy.exe
