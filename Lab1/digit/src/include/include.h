
//
// Created by YxGuo on 4/29/20.
//

#ifndef LAB1_INCLUDE_H
#define LAB1_INCLUDE_H

#include <iostream>
#include <string>



#define DIM 5
#define ZERO 26

#define GET_STATE(state, _i, _j) (state[(_i)*DIM+(_j)])

struct Node {
    char *state; //[DIM*DIM+1]
    std::pair<int, char> from_parent_movement;
    int depth;
    int h;
    struct Node *parent;
};


void printMovement(Node *n);

#endif //LAB1_INCLUDE_H
