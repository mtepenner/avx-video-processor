#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <cstdint>

// Processes a 4-channel BGRA image into a 1-channel Grayscale image using standard loops
void processGrayscaleNaive(const uint8_t* input, uint8_t* output, int width, int height);

// Processes a 4-channel BGRA image into a 1-channel Grayscale image using AVX2 Intrinsics
void processGrayscaleAVX2(const uint8_t* input, uint8_t* output, int width, int height);

#endif // PROCESSOR_H
