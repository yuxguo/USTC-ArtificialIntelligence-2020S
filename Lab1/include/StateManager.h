//
// Created by YxGuo on 4/29/20.
//

#ifndef LAB1_STATEMANAGER_H
#define LAB1_STATEMANAGER_H

#include <unordered_set>
#include <string>
#include <vector>
#include <queue>
#include <set>

#include "../include/include.h"

class StateManager {
    struct DestInfo {
        int num_pos[DIM * DIM][2];
        int seven[2];
    };

public:
    explicit StateManager(std::string destination_state);
    std::vector<std::pair<std::pair<int, char>, std::string> > getSucceedStates(const std::string &state);
    bool insertIntoCloseSet(const std::string &state);
    int hFunction(const std::string& state);

private:
    std::unordered_set<std::string> close_set;
    DestInfo dest_info;
    int hvalues[DIM * DIM][DIM][DIM];

    bool isStateInCloseSet(const std::string &state);
    std::vector<std::string> splitString(const std::string &s, const std::string &split);
    std::pair<std::pair<int, char>, std::string> stateMovement (int x, int y, char dir, const int (*a)[DIM]);

};


#endif //LAB1_STATEMANAGER_H
