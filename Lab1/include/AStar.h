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
    AStar(const std::string& init_state, const std::string& dest_state);
    ~AStar();
    Node *graphSearch();


private:
    std::priority_queue<std::pair<int, Node *> ,std::vector<std::pair<int, Node *> >, std::greater<> > fringe;
    std::vector<Node *> nodes;
    std::string init_state;
    std::string dest_state;
    StateManager *sm;

};


#endif //LAB1_ASTAR_H
