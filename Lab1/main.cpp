#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>


#include "include/AStar.h"
#include "include/IDAStar.h"
#include "include/include.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // std::cout << "initial state file name: " << argv[1] << std::endl;
        // std::cout << "dest state file name: " << argv[2] << std::endl;
        std::ifstream initFile, destFile;
        initFile.open("../inputs/input3.txt");
        destFile.open("../inputs/dest.txt");
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
        AStar a_star(init_state, dest_state);
        Node *n = a_star.graphSearch();
        printMovement(n);
    }
    return 0;
}

