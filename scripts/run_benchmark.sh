#!/bin/bash
set -e

echo ">>> Creating build directory..."
mkdir -p build
cd build

echo ">>> Generating CMake files..."
cmake ..

echo ">>> Compiling project..."
make -j$(nproc)

echo ">>> Running Benchmark Executable..."
./avx_video_processor
