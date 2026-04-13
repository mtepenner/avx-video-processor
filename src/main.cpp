#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include "processor.h"

int main(int argc, char** argv) {
    std::cout << "=========================================\n";
    std::cout << " Intel AVX2 Video Processor Benchmark \n";
    std::cout << "=========================================\n";

    // Simulate a 1080p frame (1920x1080) with 4 channels (BGRA)
    int width = 1920;
    int height = 1080;
    cv::Mat test_frame(height, width, CV_8UC4, cv::Scalar(120, 150, 200, 255));
    cv::Mat output_frame(height, width, CV_8UC1);

    int num_iterations = 1000; // Simulate processing 1000 frames
    std::cout << "Benchmarking " << num_iterations << " frames at 1080p resolution...\n\n";

    // --- Benchmark Naive Approach ---
    auto start_naive = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_iterations; i++) {
        processGrayscaleNaive(test_frame.data, output_frame.data, width, height);
    }
    auto end_naive = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> naive_ms = end_naive - start_naive;

    // --- Benchmark AVX2 Approach ---
    auto start_avx = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_iterations; i++) {
        processGrayscaleAVX2(test_frame.data, output_frame.data, width, height);
    }
    auto end_avx = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> avx_ms = end_avx - start_avx;

    // --- Results ---
    std::cout << "[Results]\n";
    std::cout << "Naive Approach : " << naive_ms.count() << " ms\n";
    std::cout << "AVX2 Approach  : " << avx_ms.count() << " ms\n";
    std::cout << "Performance    : " << (naive_ms.count() / avx_ms.count()) << "x speedup\n";
    std::cout << "=========================================\n";

    return 0;
}
