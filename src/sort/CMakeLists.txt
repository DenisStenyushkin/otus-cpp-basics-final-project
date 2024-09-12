cmake_minimum_required(VERSION 3.20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(PROJECT_SOURCES
    kalman_filter.cpp
    kalman_filter.h
    matrix.h
    munkres.cpp
    munkres.h
    track.cpp
    track.h
    tracker.cpp
    tracker.h
    utils.h
)

add_library(sort ${PROJECT_SOURCES})
