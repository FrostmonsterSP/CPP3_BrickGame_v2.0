#!/bin/bash

# Цвета для вывода в консоль
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"
PURPLE="\033[0;35m"
BOLD="\033[1m"
RESET="\033[0m"

LIB_VERSION=2.2

if [ ! -d "libs" ]; then mkdir libs; fi

if [ $(uname -m) == "x86_64" ]; then
printf "$BLUE$BOLD=>$RESET$BLUE Скачивается скомпилированная x86_64 библиотека$RESET\n"
wget https://github.com/FrostmonsterSP/BrickGameLib/releases/download/v.$LIB_VERSION/brick_game_lib-$LIB_VERSION.x86_64.tar.gz
tar -xf brick_game_lib-$LIB_VERSION.x86_64.tar.gz
rm -rf brick_game_lib-$LIB_VERSION.x86_64.tar.gz
mv engine.h libs/tetris.h
else
printf "$BLUE$BOLD=>$RESET$BLUE Скачиваются исходные коды библиотеки$RESET\n"
wget https://github.com/FrostmonsterSP/BrickGameLib/archive/refs/tags/v.$LIB_VERSION.tar.gz
tar -xf v.$LIB_VERSION.tar.gz
rm -rf v.$LIB_VERSION.tar.gz
cd BrickGameLib-v.$LIB_VERSION
make build
mv libs/libtetris.a ../libs/libtetris.a
mv src/engine.h ../libs/tetris.h
cd ../
rm -rf BrickGameLib-v.$LIB_VERSION
fi
