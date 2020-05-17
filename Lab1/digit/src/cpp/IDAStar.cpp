//
// Created by YxGuo on 4/28/20.
//
#include "../include/IDAStar.h"

static int cnt_node = 0 ;

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

void IDAStar::graphSearch() {
    Node *n = this->nodes[0];
    int threshold = this->sm->hFunction(n->state);

    this->visited.emplace(n->state, std::make_pair(true, n));
    while (true) {
        int tmp = DFS(n, threshold);
        std::cout << "current nodes: " << cnt_node << std::endl;
        if (tmp == -1) {
            return;
        }
        if (tmp == this->INF) {
            return;
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
    cnt_node++;
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

        auto n_find = this->visited.find(s.second);
        if (n_find == this->visited.end()) {
            // not found in visited
            Node *n_tmp = new Node;
            n_tmp->state = s.second;
            n_tmp->from_parent_movement = s.first;
            n_tmp->depth = n->depth + 1;
            n_tmp->parent = n;
            this->nodes.push_back(n_tmp);

            this->visited.emplace(n_tmp->state, std::make_pair(true, n_tmp));

            int tmp = DFS(n_tmp, threshold);
            this->visited[n_tmp->state].first = false;
            if (tmp == -1) {
                return -1;
            }
            if (tmp < min_val) {
                min_val = tmp;
            }

        } else {
            if (n_find->second.first == false) {
                if (n->depth+1 <= n_find->second.second->depth ) {
                    // not in stack and current depth is lower than old depth
                    Node *n_tmp = n_find->second.second; // update info
                    n_tmp->depth = n->depth + 1;
                    n_tmp->parent = n;
                    n_tmp->from_parent_movement = s.first;

                    n_find->second.first = true; // in stack
                    int tmp = DFS(n_tmp, threshold);
                    n_find->second.first = false;

                    if (tmp == -1) {
                        return -1;
                    }
                    if (tmp < min_val) {
                        min_val = tmp;
                    }
                } else {
                    delete[] s.second;
                }
            } else {
                // not need extend this node, because it won't find a better solution.
                // delete s.second, otherwise it will cause memory leak
                delete[] s.second;
            }
        }
    }
    return min_val;
}





