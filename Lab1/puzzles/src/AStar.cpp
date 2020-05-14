//
// Created by YxGuo on 4/28/20.
//
#include "../include/AStar.h"


AStar::~AStar() {
    for (auto & n : this->nodes) {
        delete[] n->state;
        delete n;
    }
    delete this->sm;
}

AStar::AStar(const char *init_state, const char *dest_state) {
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

Node *AStar::graphSearch() {
    // return the final node.
    Node *n = this->nodes[0];
    int h = this->sm->hFunction(n->state);
    int g = n->depth;
    int f = g + h;
    this->fringe.push(std::make_pair(std::make_pair(f, g), n));

    while (!fringe.empty()) {
        auto t = fringe.top();
        fringe.pop();
        f = t.first.first;
        g = t.first.second;
        n = t.second;
        if (this->check(n->state, this->dest_state)) {
            return n;
        }

        auto succeeds = this->sm->getSucceedStates(n->state);
        for (auto &s : succeeds) {
            Node *n_tmp = new Node;
            n_tmp->state = s.second;
            n_tmp->from_parent_movement = s.first;
            n_tmp->depth = n->depth + 1;
            n_tmp->parent = n;
            int n_tmp_g = n_tmp->depth;
            int n_tmp_h = this->sm->hFunction(n_tmp->state);
            int n_tmp_f = n_tmp_g + n_tmp_h;
            fringe.push(std::make_pair(std::make_pair(n_tmp_f, n_tmp_g), n_tmp));
            this->sm->insertIntoCloseSet(n_tmp->state);
            this->nodes.push_back(n_tmp);
        }
    }
    return nullptr;
}

bool AStar::check(const char* p1, const char *p2) {
    for (int i = 0; i < DIM*DIM+1; ++i) {
        if (p1[i] != p2[i]) {
            return false;
        }
    }
    return true;
}



