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
    explicit StateManager(const char *dest_state);
    std::vector<std::pair<std::pair<int, char>, char *> > getSucceedStates(const char *state);
    bool insertIntoCloseSet(const char *state);
    void clearCloseSet();
    int hFunction(const char *state);

private:
    std::unordered_set<std::string> close_set;
    DestInfo dest_info;
    int hvalues[DIM * DIM][DIM][DIM];

    bool isStateInCloseSet(const char *state);
    static std::pair<std::pair<int, char>, char *> stateMovement (int x, int y, char dir, const char *board);

};


#endif //LAB1_STATEMANAGER_H
