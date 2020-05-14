cmake_minimum_required(VERSION 3.16)
project(sudoku)

set(CMAKE_CXX_STANDARD 14)

add_executable(sudoku main.cpp src/include/CSP.h src/cpp/CSP.cpp)