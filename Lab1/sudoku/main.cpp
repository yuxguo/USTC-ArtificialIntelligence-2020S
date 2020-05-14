#include <iostream>
#include <cstdio>
#include "src/include/CSP.h"

int main() {
    int init_board[DIM][DIM];
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            scanf("%d", &init_board[i][j]);
        }
    }
    CSP csp(init_board);
    csp.CSPSolver();
}
