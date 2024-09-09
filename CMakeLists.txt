cmake_minimum_required (VERSION 3.20)
project(otus_cpp_basics_final)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(src/yolo)


add_executable(main src/main.cpp)
target_include_directories(main PUBLIC src/yolo)
target_link_libraries(main PUBLIC ${OpenCV_LIBS} yolo)
