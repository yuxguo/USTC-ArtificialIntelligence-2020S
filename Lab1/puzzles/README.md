# README

The directory is arranged as following structure.

``` shell
puzzles
├── CMakeLists.txt
├── README.md
├── include
│   ├── AStar.h
│   ├── IDAStar.h
│   ├── StateManager.h
│   └── include.h
├── inputs
│   ├── dest.txt
│   ├── input1.txt
│   ├── input2.txt
│   └── input3.txt
├── main.cpp
├── outputs
│   ├── output1.txt
│   ├── output2.txt
│   └── output3.txt
└── src
    ├── AStar.cpp
    ├── IDAStar.cpp
    ├── StateManager.cpp
    └── include.cpp
```

## Build

In `Lab1/puzzles` :

- `Cmake-Debug ` (Low Performance) : 

  ``` shell
  mkdir cmake-build-debug/ && cd cmake-build-debug/
  cmake -DCMAKE_BUILD_TYPE=Debug ..
  make
  ```

- `Cmake-Release` (Medium Performance):

  ``` shell
  mkdir cmake-build-release/ && cd cmake-build-release/
  cmake -DCMAKE_BUILD_TYPE=Release ..
  make
  ```

- `g++ -O3` (High Performance):

  ``` shell
  mkdir g++-build/ && cd g++-build/
  g++ -O3 -std=c++14 -o puzzles ../main.cpp ../src/*.cpp
  ```

## Run

Use the following format to get result: 

``` shell
./puzzles <input_file_dir> <dest_file_dir> <A / IDA> > <output_file_dir>
```

e.g. (use $A^*$ algorithm solve input1)

``` shell
./puzzles ../inputs/input1.txt ../inputs/dest.txt A > ../outputs/output1.txt
```

or (use $IDA^*$ algorithm solve input2)

``` shell
./puzzles ../inputs/input2.txt ../inputs/dest.txt IDA > ../outputs/output2.txt
```

## Remark

The code repository contains a 57-step solution of `input3.txt`. It will cost about 20 minutes and 100GiB memory to solve the solution.