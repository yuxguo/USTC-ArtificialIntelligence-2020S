//
// Created by YxGuo on 4/28/20.
//
#include "../include/IDAStar.h"

IDAStar::~IDAStar() {
    for (auto & n : this->nodes) {
        delete[] n->state;
        delete n;
    }
    delete this->sm;
}

IDAStar::IDAStar(const char *init_state, const char *dest_state) {
    Node *n = new Node;
    n->state = new char[DIM*DIM+1];
    for (int i = 0; i < DIM*DIM+1; ++i) {
        n->state[i] = init_state[i];
        this->init_state[i] = init_state[i];
        this->dest_state[i] = dest_state[i];
    }
    n->from_parent_movement.first = 0;
    n->from_parent_movement.second = '\0';
    n->depth = 0;
    n->parent = nullptr;
    this->nodes.push_back(n);
    this->sm = new StateManager(dest_state);
}

Node *IDAStar::graphSearch() {
    Node *n = this->nodes[0];
    int threshold = this->sm->hFunction(n->state);
    while (true) {
        this->sm->clearCloseSet();
        std::cout << threshold << std::endl;
        int tmp = DFS(n, threshold);
        if (tmp == -1) {
            return n;
        }
        if (tmp == this->INF) {
            return nullptr;
        }
        threshold = tmp;
    }
}



bool IDAStar::check(const char *p1, const char *p2) {
    for (int i = 0; i < DIM*DIM+1; ++i) {
        if (p1[i] != p2[i]) {
            return false;
        }
    }
    return true;
}

int IDAStar::DFS(Node *n, int threshold) {
    int f = n->depth + this->sm->hFunction(n->state);
    if (f > threshold) {
        return f;
    }
    if (this->check(n->state, this->dest_state)) {
        printMovement(n);
        return -1;
    }
    int min_val = this->INF;
    auto succeeds = this->sm->getSucceedStates(n->state);
    for (auto &s : succeeds) {
        Node *n_tmp = new Node;
        n_tmp->state = s.second;
        n_tmp->from_parent_movement = s.first;
        n_tmp->depth = n->depth + 1;
        n_tmp->parent = n;
        this->sm->insertIntoCloseSet(n_tmp->state);
        int tmp = DFS(n_tmp, threshold);
        if (tmp == -1) {
            return -1;
        }
        if (tmp < min_val) {
            min_val = tmp;
        }
        this->sm->deleteCloseSetItem(n_tmp->state);
        delete[] n_tmp->state;
        delete n_tmp;

    }
    return min_val;
}





