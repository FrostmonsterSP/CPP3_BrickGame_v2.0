#!/bin/bash

if [ $(uname -m) == "x86_64" ]; then 
wget https://github.com/FrostmonsterSP/BrickGameLib/releases/download/v.2.0/brick_game_lib-2.0.x86_64.tar.gz
tar -xf brick_game_lib-2.0.x86_64.tar.gz
rm -rf brick_game_lib-2.0.x86_64.tar.gz
mv engine.h libs/tetris.h
else 
wget https://github.com/FrostmonsterSP/BrickGameLib/archive/refs/tags/v.2.0.tar.gz
tar -xf v.2.0.tar.gz
rm -rf v.2.0.tar.gz
cd BrickGameLib-v.2.0
make build
mkdir ../libs
mv libs/libtetris.a ../libs/libtetris.a
mv src/engine.h ../libs/tetris.h
cd ../
rm -rf BrickGameLib-v.2.0
fi
