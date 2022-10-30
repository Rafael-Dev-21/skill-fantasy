# skill-fantasy
A opensource project of a survival roguelike.

## Playlist
<https://youtube.com/playlist?list=PLJsfx7Z0sXi7FZyrqkoQaW0OruHpnjxo->

## Build

Make is the tool of choice. The game only supports linux, other OSes will be added later.

## Windows
In teory, this game runs o windows, but i can't test. Do this:

* install mingw and pdcurses
* change `<ncurses.h>` to `<curses.h>` in include/skfantasy.h
* execute run.bat
