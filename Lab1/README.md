# README

The directory is arranged as following structure.

``` shell
Lab1
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

In `Lab1/` :

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
  g++ -O3 -std=c++14 -o Lab1 ../main.cpp ../src/*.cpp
  ```

## Run

Use the following format to get result: 

``` shell
./Lab1 <input_file_dir> <dest_file_dir> <A / IDA> > <output_file_dir>
```

e.g. (use $A^*$ algorithm solve input1)

``` shell
./Lab1 ../inputs/input1.txt ../inputs/dest.txt A > ../outputs/output1.txt
```

or (use $IDA^*$ algorithm solve input2)

``` shell
./Lab1 ../inputs/input2.txt ../inputs/dest.txt IDA > ../outputs/output2.txt
```

## Remark

Computing the precise solution of `input3.txt` cost lots of memory and time, so I compute a non-precise solution.

You can modify `./src/AStar.cpp, Line 59` to get a non-precise $A^*$ algorithm ($IDA^*$ is the same way), just delete 

```c++
n_tmp->depth = n->depth + 1;
```

and add 

``` c++
if (n_tmp->from_parent_movement.first == 7) {
		n_tmp->depth = n->depth - 1;
} else {
  	n_tmp->depth = n->depth + 1;	
}
```

