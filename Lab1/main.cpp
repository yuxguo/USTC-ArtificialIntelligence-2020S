#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>


#include "include/AStar.h"
#include "include/IDAStar.h"
#include "include/include.h"

int main(int argc, char *argv[]) {
//    std::priority_queue<std::pair<std::pair<int, int>, int>, std::vector<std::pair<std::pair<int, int>, int> >, std::greater<> > q;
//    q.push(std::make_pair(std::make_pair(2,3),4));
//    q.push(std::make_pair(std::make_pair(2,5),1));
//    q.push(std::make_pair(std::make_pair(3,1),2));
//    q.push(std::make_pair(std::make_pair(2,3),1));
//    while (!q.empty()) {
//        auto v = q.top();
//        q.pop();
//        std::cout << v.first.first << " "<< v.first.second << " " << v.second << std::endl;
//    }
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

