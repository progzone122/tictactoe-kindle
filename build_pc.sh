#!/bin/bash

meson setup build_pc
meson compile -C build_pc

cd build_pc
./tictactoe
cd ..