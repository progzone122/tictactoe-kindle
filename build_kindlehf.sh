#!/bin/bash

SDK="/home/diablo/x-tools/arm-kindlehf-linux-gnueabihf/meson-crosscompile.txt"

meson setup --cross-file $SDK build_kindlehf
meson compile -C build_kindlehf