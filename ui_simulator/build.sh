#!/bin/sh

set -e

cmake -S lv_port_linux -B build
cmake --build build -j$(nproc)
