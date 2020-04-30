//
// Created by YxGuo on 4/29/20.
//



#include "../include/StateManager.h"


std::vector<std::pair<std::pair<int, char>, std::string> > StateManager::getSucceedStates(const std::string &state) {
    // return a vector of ((number, dir), dir_state)
    auto v = this->splitString(state, " ");
    int board[DIM][DIM];
    for (int i = 0; i < v.size(); ++i) {
        board[i / DIM][i % DIM] = std::stoi(v[i]);
    }
    int zeros[2][2];
    int seven[2];
    int zerocnt = 0;
    // find space and 7 positions
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            if (board[i][j] == 0) {
                zeros[zerocnt][0] = i;
                zeros[zerocnt][1] = j;
                zerocnt++;
            }
            // 7(i, j-1), 7(i, j)
            //            7(i+1, j)
            if ((j-1 >= 0) && (i+1 < DIM) && (board[i][j] == 7) &&
                (board[i][j-1] == 7) && (board[i+1][j] == 7)) {
                seven[0] = i;
                seven[1] = j;
            }
        }
    }
    //std::cout << state << std::endl;
    //std::cout << "seven(x, y): " <<seven[0] << " " <<seven[1] << std::endl;
    // std::cout << zeros[0][0] << " " <<zeros[0][1] << std::endl;
    std::vector<std::pair<std::pair<int, char>, std::string> > result;
    // find possible movement, except 7
    for (auto & zero : zeros) {
        int x = zero[0];
        int y = zero[1];
        if ((x-1 >= 0) && (board[x-1][y] !=0) && (board[x-1][y] != 7)) {
            // move down
            auto res = this->stateMovement(x-1, y, 'd', board);
            if (!(this->isStateInCloseSet(res.second))) {
                result.push_back(res);
            }
        }
        if ((x+1 < DIM) && (board[x+1][y] !=0) && (board[x+1][y] != 7)) {
            // move up
            auto res = this->stateMovement(x+1, y, 'u', board);
            if (!(this->isStateInCloseSet(res.second))) {
                result.push_back(res);
            }
        }
        if ((y-1 >= 0) && (board[x][y-1] !=0) && (board[x][y-1] != 7)) {
            // move right
            auto res = this->stateMovement(x, y-1, 'r', board);
            if (!(this->isStateInCloseSet(res.second))) {
                result.push_back(res);
            }
        }
        if ((y+1 < DIM) && (board[x][y+1] !=0) && (board[x][y+1] != 7)) {
            // move left
            auto res = this->stateMovement(x, y+1, 'l', board);
            if (!(this->isStateInCloseSet(res.second))) {
                result.push_back(res);
            }
        }
    }
    // find possible movement of 7
    int x = seven[0];
    int y = seven[1];
    if ((y+1 < DIM) && (x+1 < DIM) && (board[x][y+1] == 0) && (board[x+1][y+1] == 0)) {
        // move 7 right
        auto res = this->stateMovement(x, y, 'r', board);
        if (!(this->isStateInCloseSet(res.second))) {
            result.push_back(res);
        }
    }
    if ((x-1 >= 0) && (y-1 >= 0) && (board[x-1][y] == 0) && (board[x-1][y-1] == 0)) {
        // move 7 up
        auto res = this->stateMovement(x, y, 'u', board);
        if (!(this->isStateInCloseSet(res.second))) {
            result.push_back(res);
        }
    }
    if ((y-2 >= 0) && (x+1 < DIM) && (board[x][y-2] == 0) && (board[x+1][y-1] == 0)) {
        // move 7 left
        auto res = this->stateMovement(x, y, 'l', board);
        if (!(this->isStateInCloseSet(res.second))) {
            result.push_back(res);
        }
    }
    if ((x+2 < DIM) && (y-1 >= 0) && (board[x+2][y] == 0) && (board[x+1][y-1] == 0)) {
        // move 7 down
        auto res = this->stateMovement(x, y, 'd', board);
        if (!(this->isStateInCloseSet(res.second))) {
            result.push_back(res);
        }
    }
    return result;
}

std::pair<std::pair<int, char>, std::string> StateManager::stateMovement (const int x, const int y, const char dir, const int (*board)[DIM]) {
    int tmp[DIM][DIM];
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            tmp[i][j] = board[i][j];
        }
    }
    int block_number = tmp[x][y];
    if (tmp[x][y] != 7) {
        // if is not 7 movement
        if (dir == 'u') {
            tmp[x - 1][y] = tmp[x][y];
        } else if (dir == 'd') {
            tmp[x + 1][y] = tmp[x][y];
        } else if (dir == 'r') {
            tmp[x][y + 1] = tmp[x][y];
        } else if (dir == 'l') {
            tmp[x][y - 1] = tmp[x][y];
        }
        tmp[x][y] = 0;
    } else {
        if (dir == 'u') {
            tmp[x - 1][y] = tmp[x][y];
            tmp[x - 1][y - 1] = tmp[x][y];
            tmp[x][y] = tmp[x][y];
            tmp[x][y - 1] = 0;
            tmp[x + 1][y] = 0;
        } else if (dir == 'd') {
            tmp[x + 2][y] = tmp[x][y];
            tmp[x + 1][y - 1] = tmp[x][y];
            tmp[x + 1][y] = tmp[x][y];
            tmp[x][y] = 0;
            tmp[x][y - 1] = 0;
        } else if (dir == 'r') {
            tmp[x][y + 1] = tmp[x][y];
            tmp[x + 1][y + 1] = tmp[x][y];
            tmp[x][y] = tmp[x][y];
            tmp[x][y - 1] = 0;
            tmp[x + 1][y] = 0;
        } else if (dir == 'l') {
            tmp[x][y - 1] = tmp[x][y];
            tmp[x + 1][y - 1] = tmp[x][y];
            tmp[x][y - 2] = tmp[x][y];
            tmp[x][y] = 0;
            tmp[x + 1][y] = 0;
        }
    }
    std::string s;
    for (int i = 0; i < DIM*DIM; ++i) {
        if (i == 0) {
            s += std::to_string(tmp[i / DIM][i % DIM]);
        } else {
            s += " " + std::to_string(tmp[i / DIM][i % DIM]);
        }
    }
    auto result = std::make_pair(std::make_pair(block_number, dir), s);
    return result;
}


bool StateManager::insertIntoCloseSet(const std::string &state) {
    if (this->close_set.find(state) == this->close_set.end()) {
        this->close_set.insert(state);
        return true;
    }
    return false;
}

std::vector<std::string> StateManager::splitString(const std::string &s, const std::string &split)
{
    std::vector<std::string> result;
    std::string::size_type pos1, pos2;
    pos2 = s.find(split);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        result.push_back(s.substr(pos1, pos2-pos1));
        pos1 = pos2 + split.size();
        pos2 = s.find(split, pos1);
    }
    if(pos1 != s.length())
        result.push_back(s.substr(pos1));
    return result;
}

bool StateManager::isStateInCloseSet(const std::string &state) {
    // s is the string of a state
    // if s in close_set, return true
    return !(this->close_set.find(state) == this->close_set.end());
}

int StateManager::hFunction(const std::string &state) {
    auto v = this->splitString(state, " ");
    int board[DIM][DIM];
    for (int i = 0; i < v.size(); ++i) {
        board[i / DIM][i % DIM] = std::stoi(v[i]);
    }
    int loss = 0;
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            // 7(i, j-1), 7(i, j)
            //            7(i+1, j)
            if ((j-1 >= 0) && (i+1 < DIM) && (board[i][j] == 7) &&
                (board[i][j-1] == 7) && (board[i+1][j] == 7)) {
                loss += (abs(i - this->dest_info.seven[0]) +
                        abs(j - this->dest_info.seven[1]));
            } else if ((board[i][j] != 0) && (board[i][j] != 7)) {
                loss += (abs(i -  this->dest_info.num_pos[board[i][j]][0]) +
                        abs(j -  this->dest_info.num_pos[board[i][j]][1]));
            }
        }
    }
    return loss;
}

StateManager::StateManager(std::string destination_state) {
    auto v = this->splitString(destination_state, " ");
    int board[DIM][DIM];
    for (int i = 0; i < v.size(); ++i) {
        board[i / DIM][i % DIM] = std::stoi(v[i]);
    }
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            if ((j-1 >= 0) && (i+1 < DIM) && (board[i][j] == 7) &&
                (board[i][j-1] == 7) && (board[i+1][j] == 7)) {
                this->dest_info.seven[0] = i;
                this->dest_info.seven[1] = j;
            } else if ((board[i][j] != 0) && (board[i][j] != 7)) {
                this->dest_info.num_pos[board[i][j]][0] = i;
                this->dest_info.num_pos[board[i][j]][1] = j;
            }
        }
    }
}
