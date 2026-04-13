# Silicon-Aware Video Processor

This project demonstrates the performance difference between a naive C++ implementation and a hardware-optimized AVX2 (SIMD) implementation for real-time video processing.

## Prerequisites
* CMake (3.10+)
* OpenCV (4.x)
* C++17 Compiler (GCC/Clang/MSVC) with AVX2 support
* Intel VTune Profiler (Optional, for deep hardware profiling)

## Build Instructions

Using the provided script (Linux/macOS):
```bash
bash scripts/run_benchmark.sh
