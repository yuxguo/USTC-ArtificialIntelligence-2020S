//
// Created by YxGuo on 4/28/20.
//

#ifndef LAB1_ASTAR_H
#define LAB1_ASTAR_H

#include <queue>
#include <vector>
#include <string>

#include "../include/include.h"
#include "../include/StateManager.h"



class AStar {

public:
    AStar(const char *init_state, const char *dest_state);
    ~AStar();
    Node *graphSearch();


private:

    std::priority_queue<std::pair<std::pair<int ,int>, std::pair<int, Node* > > ,std::vector<std::pair<std::pair<int ,int>, std::pair<int, Node* > >>, std::greater<> > fringe;
    std::vector<Node *> nodes;
    char init_state[DIM*DIM+1];
    char dest_state[DIM*DIM+1];
    bool check(const char* p1, const char *p2);
    StateManager *sm;

};


#endif //LAB1_ASTAR_H
