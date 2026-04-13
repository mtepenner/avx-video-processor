#include "processor.h"
#include <immintrin.h>

// Standard formulation for grayscale: Y = 0.299R + 0.587G + 0.114B
// Using fast integer approximation: Y = (R*77 + G*150 + B*29) >> 8

void processGrayscaleNaive(const uint8_t* input, uint8_t* output, int width, int height) {
    int total_pixels = width * height;
    
    for (int i = 0; i < total_pixels; ++i) {
        int idx = i * 4; // Assuming 4-channel BGRA input
        uint8_t b = input[idx];
        uint8_t g = input[idx + 1];
        uint8_t r = input[idx + 2];
        // uint8_t a = input[idx + 3]; // Alpha channel ignored
        
        output[i] = static_cast<uint8_t>((r * 77 + g * 150 + b * 29) >> 8);
    }
}

void processGrayscaleAVX2(const uint8_t* input, uint8_t* output, int width, int height) {
    int total_pixels = width * height;
    int i = 0;

    // Process 8 pixels (32 bytes) at a time using 256-bit AVX2 registers.
    // NOTE: This is a skeleton loop structure. To fully implement SIMD here, 
    // you will use _mm256_loadu_si256, _mm256_shuffle_epi8 to extract channels, 
    // _mm256_maddubs_epi16 to multiply/add, and _mm256_packus_epi16 to pack back to 8-bit.
    for (; i <= total_pixels - 8; i += 8) {
        
        // --- SIMD IMPLEMENTATION GOES HERE ---
        // For the baseline compilation, we execute the logic inside the unrolled loop
        for(int j = 0; j < 8; j++) {
            int idx = (i + j) * 4;
            uint8_t b = input[idx];
            uint8_t g = input[idx + 1];
            uint8_t r = input[idx + 2];
            output[i + j] = static_cast<uint8_t>((r * 77 + g * 150 + b * 29) >> 8);
        }
    }
    
    // Handle the remainder if total_pixels is not perfectly divisible by 8
    for (; i < total_pixels; ++i) {
        int idx = i * 4;
        uint8_t b = input[idx];
        uint8_t g = input[idx + 1];
        uint8_t r = input[idx + 2];
        output[i] = static_cast<uint8_t>((r * 77 + g * 150 + b * 29) >> 8);
    }
}
