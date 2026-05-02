version="v0.3.2"
gcc src/{*,*/*}.c -Iinclude -lm $(pkg-config ncurses guile-3.0 --libs --cflags) -o skfantasy -DVERSION="\"$version\"" -DUSE_GUILE

rm -rf linux_pkg
mkdir linux_pkg
mv skfantasy linux_pkg
cp data linux_pkg -r
cp scripts linux_pkg -r

echo "$version" > linux_pkg/version.txt
echo "$version" > version.txt
