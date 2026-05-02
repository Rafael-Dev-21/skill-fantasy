version="v0.4.0"

gcc src/{*,*/*}.c -lm -Iinclude $(pkg-config ncurses guile-3.0 --libs --cflags) -o skfantasy -DVERSION="\"$version\""

echo $version > version.txt
