//
// Created by YxGuo on 4/30/20.
//

#include "../include/include.h"

void printMovement(Node *n) {
    if (n->parent != nullptr) {
        printMovement(n->parent);
        std::cout << "(" << n->from_parent_movement.first << ", " << n->from_parent_movement.second << ")" << std::endl;
    }
}
