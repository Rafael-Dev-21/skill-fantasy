gcc src/{*,*/*}.c -lm -Iinclude $(pkg-config ncurses guile-3.0 --libs --cflags) -o skfantasy
