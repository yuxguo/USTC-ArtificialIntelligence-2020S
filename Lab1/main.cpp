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
        std::string s_init, s_dest, buffer;
        for (int i = 0; i < DIM * DIM; ++i) {
            initFile >> buffer;
            if (i == 0) {
                s_init += buffer;
            } else {
                s_init += " " + buffer;
            }
        }
        for (int i = 0; i < DIM * DIM; ++i) {
            destFile >> buffer;
            if (i == 0) {
                s_dest += buffer;
            } else {
                s_dest += " " + buffer;
            }
        }
        std::cout << s_init << std::endl;
        std::cout << s_dest << std::endl;
        AStar a_star(s_init, s_dest);
        Node *n = a_star.graphSearch();
        printMovement(n);
        std::cout << n->state << std::endl;
    }
    return 0;
}

