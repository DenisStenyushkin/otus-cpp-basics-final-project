cmake_minimum_required(VERSION 3.20)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

# CUDA
find_package(CUDA 12)
set(CMAKE_CUDA_STANDARD 12)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
# !CUDA

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
# !OpenCV

set(PROJECT_SOURCES
    inference.h
    inference.cpp
)

add_library(yolo ${PROJECT_SOURCES})
