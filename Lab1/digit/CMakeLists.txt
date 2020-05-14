cmake_minimum_required(VERSION 3.15)
project(digit)

set(CMAKE_CXX_STANDARD 14)

add_executable(digit main.cpp src/include/AStar.h src/cpp/AStar.cpp src/include/IDAStar.h src/cpp/IDAStar.cpp src/cpp/StateManager.cpp src/include/StateManager.h src/include/include.h src/cpp/include.cpp)