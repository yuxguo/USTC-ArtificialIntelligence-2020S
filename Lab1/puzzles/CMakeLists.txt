cmake_minimum_required(VERSION 3.15)
project(puzzles)

set(CMAKE_CXX_STANDARD 14)

add_executable(puzzles main.cpp include/AStar.h src/AStar.cpp include/IDAStar.h src/IDAStar.cpp src/StateManager.cpp include/StateManager.h include/include.h src/include.cpp)