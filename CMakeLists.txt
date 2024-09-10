cmake_minimum_required (VERSION 3.20)
project(otus_cpp_basics_final)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(src/yolo)


add_executable(main src/main.cpp)
target_include_directories(main PUBLIC src/yolo)
target_link_libraries(main PUBLIC ${OpenCV_LIBS} yolo)

set_target_properties(main 
                      PROPERTIES CXX_STANDARD 17 
                      CXX_STANDARD_REQUIRED ON)
target_compile_options(main PUBLIC -Wall -Wextra -Werror -pedantic)
