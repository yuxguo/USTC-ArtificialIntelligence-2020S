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
    int d_limit = this->sm->hFunction(this->nodes[0]->state) + this->nodes[0]->depth;
    while (d_limit < this->INF) {
        int next_d_limit = this->INF;
        // clear fringe
        while (!fringe.empty()) {
            fringe.pop();
        }
        // clear close set
        this->sm->clearCloseSet();
        Node *n = this->nodes[0];
        int h = this->sm->hFunction(n->state);
        int g = n->depth;
        int f = g + h;
        this->fringe.push(std::make_pair(std::make_pair(f, h), n));
        while (!fringe.empty()) {
            auto v = fringe.top();
            fringe.pop();
            n = v.second;
            f = v.first.first;
            g = n->depth;
            h = v.first.second;
            if (f > d_limit) {
                next_d_limit = (next_d_limit < f) ? next_d_limit : f;
            } else {
                if (check(n->state, this->dest_state)) {
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
                    fringe.push(std::make_pair(std::make_pair(n_tmp_f, n_tmp_h), n_tmp));
                    this->sm->insertIntoCloseSet(n_tmp->state);
                    this->nodes.push_back(n_tmp);
                }
            }
        d_limit = next_d_limit;
        }
    }
    return nullptr;
}

bool IDAStar::check(const char *p1, const char *p2) {
    for (int i = 0; i < DIM*DIM+1; ++i) {
        if (p1[i] != p2[i]) {
            return false;
        }
    }
    return true;
}





