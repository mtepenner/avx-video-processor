# 🚀 AVX2 Video Processor Benchmark

## 📖 Description
This project is a silicon-aware video processor benchmark that demonstrates the performance differences between a standard, naive C++ implementation and a hardware-optimized AVX2 (SIMD) implementation for real-time video processing. Specifically, it processes a 4-channel BGRA image into a 1-channel grayscale image by applying a fast integer approximation formula: `Y = (R*77 + G*150 + B*29) >> 8`.

## 📑 Table of Contents
- [Features](#-features)
- [Technologies Used](#-technologies-used)
- [Prerequisites](#-prerequisites)
- [Installation & Build](#-installation--build)
- [Usage](#-usage)
- [Contributing](#-contributing)
- [License](#-license)

## ✨ Features
* **Real-Time Simulation:** Simulates processing a 1080p (1920x1080) frame over 1000 iterations to accurately measure throughput.
* **Hardware Optimization:** Uses 256-bit AVX2 registers to process 8 pixels simultaneously, heavily utilizing intrinsics like `_mm256_maddubs_epi16` and `_mm256_packus_epi16`.
* **Direct Comparison:** Benchmarks both approaches side-by-side and outputs the execution time in milliseconds along with the calculated `x` speedup.

## 🛠️ Technologies Used
* **C++17**
* **OpenCV** (for image matrix handling)
* **AVX2 Intel Intrinsics**
* **CMake** (Build system)

## ⚙️ Prerequisites
Before building, ensure your environment meets the following requirements:
* **CMake** (version 3.10 or higher)
* **OpenCV** (4.x)
* **C++17 Compiler** (GCC, Clang, or MSVC) with AVX2 support `-mavx2` enabled.
* **Intel VTune Profiler** (Optional, for deep hardware profiling)

## 🚀 Installation & Build

You can quickly build and run the benchmark using the included shell script on Linux/macOS systems:

```bash
bash scripts/run_benchmark.sh
````

*(Note: This script automatically generates a `build` directory, configures CMake, compiles via `make`, and executes the benchmark).*

### Manual Build

If you prefer to build it manually:

```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```

## 💻 Usage

Once compiled, run the executable to see the performance comparison:

```bash
./avx_video_processor
```

The program will output the total processing time for 1000 1080p frames using both the standard CPU approach and the SIMD approach, followed by the calculated speedup multiplier.

## 🤝 Contributing

Contributions, issues, and feature requests are welcome\!
Feel free to check the issues page if you want to contribute.

## 📄 License

This project is licensed under the [MIT License]
