//
// Created by YxGuo on 5/14/20.
//

#include "../include/CSP.h"

CSP::CSP(int (*init)[DIM]) {
    this->state.remain = 0;
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            this->state.board[i][j] = init[i][j];
            if (init[i][j] == 0) {
                this->state.remain++;
            }
            for (int k = 0; k < DIM; ++k) {
                this->state.domain[i][j][k] = -1;
            }
        }
    }
    this->inference();
}

void CSP::printSolution() {
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            printf("%d ", this->state.board[i][j]);
        }
        printf("\n");
    }
    printf("STEP: %d", this->step);
}

void CSP::CSPSolver() {
    bool result = this->DFS();
    if (result) {
        this->printSolution();
    }

}

bool CSP::DFS() {
    this->step++;
    if (this->state.remain == 0) {
        return true;
    }
    // auto n = this->degree();
    // auto n = this->MRV();
    auto n = this->MRVDegree();
    // auto n = this->plainSelect();
    // auto n = this->degreeMRV();
    int x = n.first;
    int y = n.second;
    State old_state = this->state;
    for (int k = 0; k < DIM; ++k) {
        int val = this->state.domain[x][y][k];
        if (val == -1) {
            continue;
        }
        this->state.board[x][y] = val;
        this->state.remain--;
        if (!this->inference()) {
            this->state = old_state;
            continue;
        }

//        if (!this->check(x, y)) {
//            this->state = old_state;
//            continue;
//        }
        bool result = this->DFS();
        if (result) {
            return true;
        } else {
            this->state = old_state;
        }
    }
    return false;
}

std::pair<int, int> CSP::degree() {
    int idx_i;
    int idx_j;
    int idx_cnt = -1;
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            if (this->state.board[i][j] == 0) {
                int cnt = 0;
                for (int _i = 0; _i < DIM; ++_i) {
                    for (int _j = 0; _j < DIM; ++_j) {
                        if (this->state.board[_i][_j] == 0 && i != _i && j != _j) {
                            if (i == j && _i == _j) {
                                cnt++;
                            }
                            if (i + j == DIM-1 && _i + _j == DIM-1) {
                                cnt++;
                            }
                            if (i == _i) {
                                cnt++;
                            }
                            if (j == _j) {
                                cnt++;
                            }
                            if (((_i / 3 * 3) == (i / 3 * 3)) && ((_j / 3 * 3) == (j / 3 * 3))) {
                                cnt++;
                            }

                        }
                    }
                }
                if (cnt > idx_cnt) {
                    idx_cnt = cnt;
                    idx_i = i;
                    idx_j = j;
                }
            }
        }
    }
    return std::make_pair(idx_i, idx_j);
}

bool CSP::inference() {
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            if (this->state.board[i][j] == 0) {
                int tmp[DIM] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                // diag limit
                if (i == j) {
                    for (int k = 0; k < DIM; ++k) {
                        if (k != i && this->state.board[k][k] != 0) {
                            tmp[this->state.board[k][k]-1] = -1;
                        }
                    }
                }
                if (i + j == DIM-1) {
                    for (int k = 0; k < DIM; ++k) {
                        if (k != i && this->state.board[k][DIM-1-k] != 0) {
                            tmp[this->state.board[k][DIM-1-k]-1] = -1;
                        }
                    }
                }
                // row limit
                for (int k = 0; k < DIM; ++k) {
                    if (k != j && this->state.board[i][k] != 0) {
                        tmp[this->state.board[i][k]-1] = -1;
                    }
                }

                // col limit
                for (int k = 0; k < DIM; ++k) {
                    if (k != i && this->state.board[k][j] != 0) {
                        tmp[this->state.board[k][j]-1] = -1;
                    }
                }

                // square limit
                int x0 = i / 3 * 3;
                int y0 = j / 3 * 3;
                for (int k = 0; k < DIM; ++k) {
                    int x = x0 + k / 3;
                    int y = y0 + k % 3;
                    if (i != x && j != y && this->state.board[x][y] != 0) {
                        tmp[this->state.board[x][y]-1] = -1;
                    }
                }
                int flag = 0;
                for (int k = 0; k < DIM; ++k) {
                    if (tmp[k] != -1) {
                        flag = 1;
                    }
                }
                if (flag == 0) {
                    return false;
                } else {
                    for (int k = 0; k < DIM; ++k) {
                        this->state.domain[i][j][k] = tmp[k];
                    }
                }
            }
        }
    }
    return true;
}

std::pair<int, int> CSP::plainSelect() {
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            if (this->state.board[i][j] == 0) {
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(0, 0);
}

bool CSP::check(int x, int y) {
    int flag = true;
    // diag limit
    if (x == y) {
        for (int k = 0; k < DIM; ++k) {
            if (k != x) {
                if (this->state.board[k][k] == this->state.board[x][y]) {
                    flag = false;
                }
            }
        }
    }
    if (x + y == DIM-1) {
        for (int k = 0; k < DIM; ++k) {
            if (k != x) {
                if (this->state.board[k][DIM-1-k] == this->state.board[x][y]) {
                    flag = false;
                }
            }
        }
    }
    // row limit
    for (int k = 0; k < DIM; ++k) {
        if (k != y) {
            if (this->state.board[x][k] == this->state.board[x][y]) {
                flag = false;
            }
        }
    }

    //col limit
    for (int k = 0; k < DIM; ++k) {
        if (k != x) {
            if (this->state.board[k][y] == this->state.board[x][y]) {
                flag = false;
            }
        }
    }
    int x0 = x / 3 * 3;
    int y0 = y / 3 * 3;
    for (int k = 0; k < DIM; ++k) {
        int _x = x0 + k / 3;
        int _y = y0 + k % 3;
        if (_x != x && _y != y ) {
            if (this->state.board[x][y] == this->state.board[_x][_y]) {
                flag = false;
            }
        }
    }
    return flag;
}

std::pair<int, int> CSP::MRV() {
    int cnt = 1000;
    int idx_i = 0;
    int idx_j = 0;
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            if (this->state.board[i][j] == 0) {
                int tmp_cnt = 0;
                for (int k = 0; k < DIM; ++k) {
                    if (this->state.domain[i][j][k] != -1) {
                        tmp_cnt++;
                    }
                }
                if (tmp_cnt < cnt) {
                    cnt = tmp_cnt;
                    idx_i = i;
                    idx_j = j;
                }
            }
        }
    }
    return std::make_pair(idx_i, idx_j);
}

std::pair<int, int> CSP::MRVDegree() {
    int cnt = 1000;
    int idx_i = 0;
    int idx_j = 0;
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            if (this->state.board[i][j] == 0) {
                int tmp_cnt = 0;
                for (int k = 0; k < DIM; ++k) {
                    if (this->state.domain[i][j][k] != -1) {
                        tmp_cnt++;
                    }
                }
                if (tmp_cnt < cnt) {
                    cnt = tmp_cnt;
                    idx_i = i;
                    idx_j = j;
                }
            }
        }
    }
//    return std::make_pair(idx_i, idx_j);
    std::vector<std::pair<int, int> > list;
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            if (this->state.board[i][j] == 0) {
                int tmp_cnt = 0;
                for (int k = 0; k < DIM; ++k) {
                    if (this->state.domain[i][j][k] != -1) {
                        tmp_cnt++;
                    }
                }
                if (tmp_cnt == cnt) {

                    list.emplace_back(i, j);
                }
            }
        }
    }

    cnt = -1;
    for (auto &item : list) {
        int i = item.first;
        int j = item.second;
        int tmp_cnt = 0;
        for (int _i = 0; _i < DIM; ++_i) {
            for (int _j = 0; _j < DIM; ++_j) {
                if (this->state.board[_i][_j] == 0 && i != _i && j != _j) {
                    if (i == j && _i == _j) {
                        tmp_cnt++;
                    }
                    if (i + j == DIM-1 && _i + _j == DIM-1) {
                        tmp_cnt++;
                    }
                    if (i == _i) {
                        tmp_cnt++;
                    }
                    if (j == _j) {
                        tmp_cnt++;
                    }
                    if (((_i / 3 * 3) == (i / 3 * 3)) && ((_j / 3 * 3) == (j / 3 * 3))) {
                        tmp_cnt++;
                    }
                    if (tmp_cnt > cnt) {
                        cnt = tmp_cnt;
                        idx_i = i;
                        idx_j = j;
                    }
                }
            }
        }
    }
    return std::make_pair(idx_i, idx_j);
}

std::pair<int, int> CSP::degreeMRV() {
    int idx_i;
    int idx_j;
    int idx_cnt = -1;
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            if (this->state.board[i][j] == 0) {
                int cnt = 0;
                for (int _i = 0; _i < DIM; ++_i) {
                    for (int _j = 0; _j < DIM; ++_j) {
                        if (this->state.board[_i][_j] == 0 && i != _i && j != _j) {
                            if (i == j && _i == _j) {
                                cnt++;
                            } else if (i + j == DIM-1 && _i + _j == DIM-1) {
                                cnt++;
                            } else if (i == _i) {
                                cnt++;
                            } else if (j == _j) {
                                cnt++;
                            } else if (((_i / 3 * 3) == (i / 3 * 3)) && ((_j / 3 * 3) == (j / 3 * 3))) {
                                cnt++;
                            }

                        }
                    }
                }
                if (cnt > idx_cnt) {
                    idx_cnt = cnt;
                    idx_i = i;
                    idx_j = j;
                }
            }
        }
    }
    std::vector<std::pair<int, int> > list;
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            if (this->state.board[i][j] == 0) {
                int cnt = 0;
                for (int _i = 0; _i < DIM; ++_i) {
                    for (int _j = 0; _j < DIM; ++_j) {
                        if (this->state.board[_i][_j] == 0 && i != _i && j != _j) {
                            if (i == j && _i == _j) {
                                cnt++;
                            } else if (i + j == DIM-1 && _i + _j == DIM-1) {
                                cnt++;
                            } else if (i == _i) {
                                cnt++;
                            } else if (j == _j) {
                                cnt++;
                            } else if (((_i / 3 * 3) == (i / 3 * 3)) && ((_j / 3 * 3) == (j / 3 * 3))) {
                                cnt++;
                            }

                        }
                    }
                }
                if (cnt == idx_cnt) {
                    list.emplace_back(i, j);
                }
            }
        }
    }
    int cnt = 1000;
    idx_i = 0;
    idx_j = 0;
    for (auto & item : list) {
        int i = item.first;
        int j = item.second;
        if (this->state.board[i][j] == 0) {
            int tmp_cnt = 0;
            for (int k = 0; k < DIM; ++k) {
                if (this->state.domain[i][j][k] != -1) {
                    tmp_cnt++;
                }
            }
            if (tmp_cnt < cnt) {
                cnt = tmp_cnt;
                idx_i = i;
                idx_j = j;
            }
        }
    }
    return std::make_pair(idx_i, idx_j);
}

