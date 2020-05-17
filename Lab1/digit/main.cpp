#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>


#include "src/include/AStar.h"
#include "src/include/IDAStar.h"
#include "src/include/include.h"

int main(int argc, char *argv[]) {
    if (argc == 4) {
        std::ifstream initFile, destFile;
        initFile.open(argv[1]);
        destFile.open(argv[2]);
        char *init_state = new char[DIM*DIM+1];
        char *dest_state = new char[DIM*DIM+1];
        std::string buffer;

        for (int i = 0; i < DIM * DIM; ++i) {
            initFile >> buffer;
            char num = (char )std::stoi(buffer);
            if (num == 0) {
                init_state[i] = ZERO;
            } else {
                init_state[i] = num;
            }
        }
        for (int i = 0; i < DIM * DIM; ++i) {
            destFile >> buffer;
            char num = (char )std::stoi(buffer);
            if (num == 0) {
                dest_state[i] = ZERO;
            } else {
                dest_state[i] = num;
            }
        }
        init_state[DIM*DIM] = '\0';
        dest_state[DIM*DIM] = '\0';
        if (argv[3][0] == 'A') {
            AStar a_star(init_state, dest_state);
            Node *n = a_star.graphSearch();
            printMovement(n);
        } else {
            IDAStar ida_star(init_state, dest_state);
            ida_star.graphSearch();
        }
    }
    return 0;
}

