//
// Created by YxGuo on 4/29/20.
//

#ifndef LAB1_INCLUDE_H
#define LAB1_INCLUDE_H

#include <iostream>
#include <string>



#define DIM 5

struct Node {
    std::string state;
    std::pair<int, char> from_parent_movement;
    int depth;
    struct Node *parent;
};

void printMovement(Node *n);

#endif //LAB1_INCLUDE_H
