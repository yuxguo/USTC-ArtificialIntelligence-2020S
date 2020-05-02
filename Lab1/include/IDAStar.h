//
// Created by YxGuo on 4/28/20.
//

#ifndef LAB1_IDASTAR_H
#define LAB1_IDASTAR_H

#include <queue>
#include <vector>

#include "include.h"
#include "../include/StateManager.h"

class IDAStar {

public:
    IDAStar(const char *init_state, const char *dest_state);
    ~IDAStar();
    Node *graphSearch();
private:
    std::priority_queue<std::pair<std::pair<int ,int>, Node* > ,std::vector<std::pair<std::pair<int ,int>, Node* > >, std::greater<> > fringe;
    std::vector<Node *> nodes;
    char init_state[DIM*DIM+1];
    char dest_state[DIM*DIM+1];
    bool check(const char* p1, const char *p2);
    StateManager *sm;
    const int INF = 100000;
};

#endif //LAB1_IDASTAR_H
