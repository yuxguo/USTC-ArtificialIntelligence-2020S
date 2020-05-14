# README

- Author: YuxuanGuo
- ID: PB17111568

The directory is organized into the following structure.

``` shell
Lab1/
├── README.md
├── digit
│   ├── CMakeLists.txt
│   ├── inputs
│   │   ├── dest.txt
│   │   ├── input1.txt
│   │   ├── input2.txt
│   │   └── input3.txt
│   ├── main.cpp
│   ├── outputs
│   │   ├── output1.txt
│   │   ├── output2.txt
│   │   └── output3.txt
│   └── src
│       ├── cpp
│       │   ├── AStar.cpp
│       │   ├── IDAStar.cpp
│       │   ├── StateManager.cpp
│       │   └── include.cpp
│       └── include
│           ├── AStar.h
│           ├── IDAStar.h
│           ├── StateManager.h
│           └── include.h
└── sudoku
    ├── CMakeLists.txt
    ├── inputs
    │   ├── sudoku01.txt
    │   ├── sudoku02.txt
    │   └── sudoku03.txt
    ├── main.cpp
    └── src
        ├── cpp
        │   └── CSP.cpp
        └── include
            └── CSP.h
```

## Digit

### Build

In `Lab1/digit` :

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
  g++ -O3 -std=c++14 -o digit ../main.cpp ../src/cpp/*.cpp
  ```

### Run

In `Lab1/digit/<build-dir>` :

Use the following format to get result: 

``` shell
./digit <input_file_dir> <dest_file_dir> <A / IDA> > <output_file_dir>
```

e.g. (use $A^*$ algorithm solve input1)

``` shell
./digit ../inputs/input1.txt ../inputs/dest.txt A > ../outputs/output1.txt
```

or (use $IDA^*$ algorithm solve input2)

``` shell
./digit ../inputs/input2.txt ../inputs/dest.txt IDA > ../outputs/output2.txt
```

## Sudoku

### Build

In `Lab1/sudoku` :

- `Cmake-Debug` :

  ``` shell
  mkdir cmake-build-debug/ && cd cmake-build-debug/
  cmake -DCMAKE_BUILD_TYPE=Debug ..
  make
  ```

- `Cmake-Release` :

  ``` shell
  mkdir cmake-build-release/ && cd cmake-build-release/
  cmake -DCMAKE_BUILD_TYPE=Release ..
  make
  ```

### Run

In `Lab1/sudoku/<build-dir>`

``` shell
cat ../inputs/<sudoku-file>.txt | ./sudoku
```



## Remarks

The code repository contains a 57-step solution of `Lab1/digit/inputs/input3.txt` in `Lab1/digit/outputs/output3.txt`. It will cost about 20 minutes and 100GiB memory to get the solution.