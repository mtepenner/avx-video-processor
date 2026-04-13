cmake_minimum_required(VERSION 3.10)
project(avx_video_processor)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable AVX2 and high-level compiler optimizations
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2 -O3 -Wall")

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include directories
include_directories(include ${OpenCV_INCLUDE_DIRS})

# Create executable
add_executable(avx_video_processor 
    src/main.cpp 
    src/processor.cpp
)

# Link OpenCV libraries
target_link_libraries(avx_video_processor ${OpenCV_LIBS})
