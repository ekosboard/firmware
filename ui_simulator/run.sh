#!/bin/sh

set -e

cmake --build build -j$(nproc)
./build/bin/lvglsim -b wayland
