#!/bin/bash

# Цвета для вывода в консоль
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"
PURPLE="\033[0;35m"
BOLD="\033[1m"
RESET="\033[0m"

if [ ! -d "libs" ]; then mkdir libs; fi

if [ $(uname -m) == "x86_64" ]; then
printf "$BLUE$BOLD=>$RESET$BLUE Скачивается скомпилированная x86_64 библиотека$RESET\n"
wget https://github.com/FrostmonsterSP/BrickGameLib/releases/download/v.2.2/brick_game_lib-2.2.x86_64.tar.gz
tar -xf brick_game_lib-2.0.x86_64.tar.gz
rm -rf brick_game_lib-2.0.x86_64.tar.gz
mv engine.h libs/tetris.h
else
printf "$BLUE$BOLD=>$RESET$BLUE Скачиваются исходные коды библиотеки$RESET\n"
wget https://github.com/FrostmonsterSP/BrickGameLib/archive/refs/tags/v.2.2.tar.gz
tar -xf v.2.0.tar.gz
rm -rf v.2.0.tar.gz
cd BrickGameLib-v.2.0
make build
mv libs/libtetris.a ../libs/libtetris.a
mv src/engine.h ../libs/tetris.h
cd ../
rm -rf BrickGameLib-v.2.0
fi
