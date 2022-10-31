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
windows: INCLUDES=-Iinclude -I.
windows: LIBS=-l./pdcurses
windows: ITEMS=skfantasy.exe pdcurses.dll
windows: PACKAGE=skfantasy-windows.zip
windows: pdcurses build package clean


linux: build package clean

build:
	$(CC) $(SOURCES) $(CFLAGS) -o $(BIN)

package:
	zip $(PACKAGE) $(ITEMS)

pdcurses:
	@ echo Baixando pdcurses…
	@ curl -L -o pdcurses.zip https://sourceforge.net/projects/pdcurses/files/pdcurses/3.4/pdc34dllw.zip/download
	@ echo Descompactando…
	@ unzip pdcurses.zip


run: build
	./skfantasy

clean:
	$(RM) skfantasy skfantasy.exe pdcurses* curses.h panel.h