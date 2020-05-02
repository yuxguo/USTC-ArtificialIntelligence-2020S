//
// Created by YxGuo on 4/29/20.
//



#include "../include/StateManager.h"


std::vector<std::pair<std::pair<int, char>, char *> > StateManager::getSucceedStates(const char *state) {
    // return a vector of ((number, dir), dir_state)
    int zeros[2][2];
    int seven[2];
    int zerocnt = 0;
    // find space and 7 positions
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            if (GET_STATE(state, i, j) == ZERO) {
                // std::cout << 1 <<std::endl;
                zeros[zerocnt][0] = i;
                zeros[zerocnt][1] = j;
                zerocnt++;
            }

            // 7(i, j-1), 7(i, j)
            //            7(i+1, j)
            if ((j-1 >= 0) && (i+1 < DIM) && (GET_STATE(state, i, j) == 7) &&
                (GET_STATE(state, i, j-1) == 7) && (GET_STATE(state, i+1, j) == 7)) {
                seven[0] = i;
                seven[1] = j;
            }
        }
    }

    std::vector<std::pair<std::pair<int, char>, char *> > result;
    // find possible movement, except 7
    for (auto & zero : zeros) {
        int x = zero[0];
        int y = zero[1];
        if ((x-1 >= 0) && (GET_STATE(state, x-1, y) != ZERO) && (GET_STATE(state, x-1, y) != 7)) {
            // move down
            auto res = this->stateMovement(x-1, y, 'd', state);
            if (!(this->isStateInCloseSet(res.second))) {
                result.push_back(res);
            }
        }
        if ((x+1 < DIM) && (GET_STATE(state, x+1, y) != ZERO) && (GET_STATE(state, x+1, y) != 7)) {
            // move up
            auto res = this->stateMovement(x+1, y, 'u', state);
            if (!(this->isStateInCloseSet(res.second))) {
                result.push_back(res);
            }
        }
        if ((y-1 >= 0) && (GET_STATE(state, x, y-1) != ZERO) && (GET_STATE(state, x, y-1) != 7)) {
            // move right
            auto res = this->stateMovement(x, y-1, 'r', state);
            if (!(this->isStateInCloseSet(res.second))) {
                result.push_back(res);
            }
        }
        if ((y+1 < DIM) && (GET_STATE(state, x, y+1) != ZERO) && (GET_STATE(state, x, y+1) != 7)) {
            // move left
            auto res = this->stateMovement(x, y+1, 'l', state);
            if (!(this->isStateInCloseSet(res.second))) {
                result.push_back(res);
            }
        }
    }
    // find possible movement of 7
    int x = seven[0];
    int y = seven[1];

    if ((y+1 < DIM) && (x+1 < DIM) && (GET_STATE(state, x, y+1) == ZERO) && (GET_STATE(state, x+1, y+1) == ZERO)) {
        // move 7 right
        auto res = this->stateMovement(x, y, 'r', state);
        if (!(this->isStateInCloseSet(res.second))) {
            result.push_back(res);
        }
    }
    if ((x-1 >= 0) && (y-1 >= 0) && (GET_STATE(state, x-1, y) == ZERO) && (GET_STATE(state, x-1, y-1) == ZERO)) {
        // move 7 up
        auto res = this->stateMovement(x, y, 'u', state);
        if (!(this->isStateInCloseSet(res.second))) {
            result.push_back(res);
        }
    }

    if ((y-2 >= 0) && (x+1 < DIM) && (GET_STATE(state, x, y-2) == ZERO) && (GET_STATE(state, x+1, y-1) == ZERO)) {
        // move 7 left

        auto res = this->stateMovement(x, y, 'l', state);
        if (!(this->isStateInCloseSet(res.second))) {
            result.push_back(res);
        }
    }

    if ((x+2 < DIM) && (y-1 >= 0) && (GET_STATE(state, x+2, y) == ZERO) && (GET_STATE(state, x+1, y-1) == ZERO)) {
        // move 7 down
        auto res = this->stateMovement(x, y, 'd', state);
        if (!(this->isStateInCloseSet(res.second))) {
            result.push_back(res);
        }
    }
    return result;
}

std::pair<std::pair<int, char>, char *> StateManager::stateMovement (const int x, const int y, const char dir, const char *board) {

    // alloc in this function, delete in AStar.graphSearch()
    char *tmp = new char[DIM*DIM+1];
    for (int i = 0; i < DIM*DIM+1; ++i) {
        tmp[i] = board[i];
    }
    int block_number = GET_STATE(tmp, x, y);
    if (GET_STATE(tmp, x, y) != 7) {
        // if is not 7 movement
        if (dir == 'u') {
            GET_STATE(tmp, x-1, y) = GET_STATE(tmp, x, y);
        } else if (dir == 'd') {
            GET_STATE(tmp, x+1, y) = GET_STATE(tmp, x, y);
        } else if (dir == 'r') {
            GET_STATE(tmp, x, y+1) = GET_STATE(tmp, x, y);
        } else if (dir == 'l') {
            GET_STATE(tmp, x, y-1) = GET_STATE(tmp, x, y);
        }
        GET_STATE(tmp, x, y) = ZERO;
    } else {
        if (dir == 'u') {
            GET_STATE(tmp, x-1, y) = GET_STATE(tmp, x, y);
            GET_STATE(tmp, x-1, y-1) = GET_STATE(tmp, x, y);
            GET_STATE(tmp, x, y) = GET_STATE(tmp, x, y);
            GET_STATE(tmp, x, y-1) = ZERO;
            GET_STATE(tmp, x+1, y) = ZERO;
        } else if (dir == 'd') {
            GET_STATE(tmp, x+2, y) = GET_STATE(tmp, x, y);
            GET_STATE(tmp, x+1, y-1) = GET_STATE(tmp, x, y);
            GET_STATE(tmp, x+1, y) = GET_STATE(tmp, x, y);
            GET_STATE(tmp, x, y) = ZERO;
            GET_STATE(tmp, x, y-1) = ZERO;
        } else if (dir == 'r') {
            GET_STATE(tmp, x, y+1) = GET_STATE(tmp, x, y);
            GET_STATE(tmp, x+1, y+1) = GET_STATE(tmp, x, y);
            GET_STATE(tmp, x, y) = GET_STATE(tmp, x, y);
            GET_STATE(tmp, x, y-1) = ZERO;
            GET_STATE(tmp, x+1, y) = ZERO;
        } else if (dir == 'l') {
            GET_STATE(tmp, x, y-1) = GET_STATE(tmp, x, y);
            GET_STATE(tmp, x+1, y-1) = GET_STATE(tmp, x, y);
            GET_STATE(tmp, x, y-2) = GET_STATE(tmp, x, y);
            GET_STATE(tmp, x, y) = ZERO;
            GET_STATE(tmp, x+1, y) = ZERO;
        }
    }
    auto result = std::make_pair(std::make_pair(block_number, dir), tmp);
    return result;
}


bool StateManager::insertIntoCloseSet(const char *state) {
    std::string s(state);
    if (this->close_set.find(s) == this->close_set.end()) {
        this->close_set.insert(s);
        return true;
    }
    return false;
}



bool StateManager::isStateInCloseSet(const char *state) {
    // s is the string of a state
    // if s in close_set, return true
    std::string s(state);
    return !(this->close_set.find(s) == this->close_set.end());
}

int StateManager::hFunction(const char *state) {
    int loss = 0;
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            // 7(i, j-1), 7(i, j)
            //            7(i+1, j)
            if ((j-1 >= 0) && (i+1 < DIM) && (GET_STATE(state, i, j) == 7) &&
                (GET_STATE(state, i, j-1) == 7) && (GET_STATE(state, i+1, j) == 7)) {
                loss += this->hvalues[GET_STATE(state, i, j)][i][j];
            } else if ((GET_STATE(state, i, j) != ZERO) && (GET_STATE(state, i, j) != 7)) {
                loss += this->hvalues[GET_STATE(state, i, j)][i][j];
            }
        }
    }
    return loss;
}

StateManager::StateManager(const char *dest_state) {
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            if ((j-1 >= 0) && (i+1 < DIM) && (GET_STATE(dest_state, i, j) == 7) &&
                (GET_STATE(dest_state, i, j-1) == 7) && (GET_STATE(dest_state, i+1, j) == 7)) {
                this->dest_info.seven[0] = i;
                this->dest_info.seven[1] = j;
            } else if ((GET_STATE(dest_state, i, j) != ZERO) && (GET_STATE(dest_state, i, j) != 7)) {
                this->dest_info.num_pos[GET_STATE(dest_state, i, j)][0] = i;
                this->dest_info.num_pos[GET_STATE(dest_state, i, j)][1] = j;
            }
        }
    }

    for (int k = 0; k < DIM * DIM; ++k) {
        for (int i = 0; i < DIM; ++i) {
            for (int j = 0; j < DIM; ++j) {
                // h value of k, when k in (i,j)
                if (k != ZERO && k != 7) {
                    this->hvalues[k][i][j] = (abs(i -  this->dest_info.num_pos[k][0]) +
                                             abs(j -  this->dest_info.num_pos[k][1]));
                }
                else if (k == 7) {
                    if ((j-1 >= 0) && (i+i < DIM)) {
                        this->hvalues[k][i][j] = (abs(i - this->dest_info.seven[0]) +
                                                  abs(j - this->dest_info.seven[1]));
                    } else {
                        this->hvalues[k][i][j] = -1;
                    }
                }
            }
        }
    }
}

void StateManager::clearCloseSet() {
    this->close_set.clear();
}
