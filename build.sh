#!/usr/bin/env sh

set -ex

LIBS=`pkg-config --libs "sdl2, SDL2_image"`
CFLAGS=`pkg-config --cflags "sdl2, SDL2_image"`

gcc -Wall -Wextra -Wpedantic -ggdb -o main main.c
