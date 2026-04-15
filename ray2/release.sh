#!/usr/bin/env bash
set -euo pipefail
clang -O2 -s -Wall -Wextra -Werror -pedantic -oskfantasy main.c -lncurses -lm
