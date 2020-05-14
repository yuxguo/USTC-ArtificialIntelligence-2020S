//
// Created by YxGuo on 5/14/20.
//

#ifndef SUDOKU_CSP_H
#define SUDOKU_CSP_H

#define DIM 9

#include <iostream>
#include <cstdio>
#include <vector>

class CSP {

    struct State {
        int board[DIM][DIM];
        int domain[DIM][DIM][DIM]; // domain[i][j][0] == -1 means it can not modify
        int remain;
    };

public:
    CSP(int (*init)[DIM]);

    void CSPSolver();


private:
    int step = 0;
    State state{};
    void printSolution();
    bool DFS();
    std::pair<int, int> degree();
    bool inference(); // shrink domain
    std::pair<int, int> plainSelect();
    bool check(int x, int y);
    std::pair<int, int> MRV();
    std::pair<int, int> MRVDegree();
    std::pair<int, int> degreeMRV();
};


#endif //SUDOKU_CSP_H
