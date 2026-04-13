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
        // 1. Load 32 bytes (8 BGRA pixels) into a 256-bit register
        __m256i pixels = _mm256_loadu_si256((const __m256i*)&input[i * 4]);

        // 2. We need to multiply B, G, and R by their respective weights (29, 150, 77).
        // Since AVX2 doesn't have a direct 8-bit 3-way multiply-add, we use a trick.
        // We shuffle the bytes so we can use _mm256_maddubs_epi16 (multiply and add adjacent bytes).
        
        // Create a multiplier register: [B_weight, G_weight, R_weight, 0] repeated
        __m256i weights = _mm256_set1_epi32(
            (0 << 24) | (77 << 16) | (150 << 8) | 29
        );

        // Multiply B*29 + G*150. (The R channel and Alpha channel are also multiplied but kept separate for now)
        __m256i bg_rg = _mm256_maddubs_epi16(pixels, weights);

        // 3. We now have 16-bit intermediate sums. We need to add the (R*77) part to the (B*29 + G*150) part.
        // We do this by horizontally adding adjacent 16-bit integers.
        __m256i ones = _mm256_set1_epi16(1); 
        __m256i sum = _mm256_madd_epi16(bg_rg, ones); // This results in 32-bit integers of our full sum

        // 4. Bit shift right by 8 (which is equivalent to dividing by 256)
        __m256i shifted = _mm256_srli_epi32(sum, 8);

        // 5. We now have 8 32-bit integers. We need to pack them down to 8 8-bit integers (1 byte per pixel).
        // First pack 32-bit to 16-bit
        __m256i pack16 = _mm256_packs_epi32(shifted, shifted);
        
        // Then pack 16-bit to 8-bit. 
        // Note: AVX2 packs act weirdly across the 128-bit lanes, so we need a permute to get them in order.
        __m256i pack8 = _mm256_packus_epi16(pack16, pack16);
        __m256i permuted = _mm256_permutevar8x32_epi32(pack8, _mm256_setr_epi32(0, 4, 1, 5, 2, 6, 3, 7));

        // 6. Store the final 8 bytes (8 grayscale pixels) to the output array
        // We cast to double to write exactly 64 bits (8 bytes) cleanly
        *reinterpret_cast<double*>(&output[i]) = _mm_cvtsi64_f64(_mm256_extracti128_si256(permuted, 0));
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
