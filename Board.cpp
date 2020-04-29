//
// Created by thong on 4/12/20.
//

#include "Board.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "global.h"

Board::Board(int size) : grid{0}, log{0} {
    this->board_size = size;
    for(int row = 1; row <= board_size; row++) {
        for (int col = 1; col <= board_size; col++) {
            grid[row][col] = 0;
            log[row][col] = EMPTY_CELL;
        }
    }
}

bool Board::put_card(int row, int col, int val, int player) {
    if (!can_put_card(row, col)) return false;
    grid[row][col] = val;
    log[row][col] = player;
    return true;
}

bool Board::check_at(int row, int col) {
    char x[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    char y[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

    int sum = 0;
    for(unsigned char i = 0; i < 9; i++) {
        sum += grid[row + x[i]][col + y[i]];
    }
    return sum <= 15;
}

void Board::check_all() {
    std::pair<unsigned char, unsigned char> remove[64];
    int len = 0;
    for(int row = 1; row <= board_size; row++) {
        for (int col = 1; col <= board_size; col++) {
            if (!check_at(row, col)) remove[len++] = std::pair<unsigned char, unsigned char>(row, col);
        }
    }

    for(int i = 0; i < len; i++) {
        auto pos = remove[i];
        grid[pos.first][pos.second] = 0;
    }
}

void Board::reset() {
    for(int row = 1; row <= board_size; row++) {
        for (int col = 1; col <= board_size; col++) {
            grid[row][col] = 0;
            log[row][col] = EMPTY_CELL;
        }
    }
}

int Board::get_cell(int row, int col) {
    return (int) grid[row][col];
}

void Board::print_board() {
    std::cout << "===================================" << std::endl;
    for(int row = 1; row <= board_size; row++) {
        for(int col = 1; col <= board_size; col++) {
            int cell = get_cell(row, col);
            if (log[row][col] != EMPTY_CELL && cell == 0) {
                std::cout << std::setw(4) << 'X';
            } else {
                if (log[row][col] == HUMAN_CELL) {
                    std::cout << "\033[1;31m" << std::setw(4)  << cell << "\033[0m";
                } else if (log[row][col] == AI_CELL) {
                    std::cout << "\033[1;32m" << std::setw(4) << cell << "\033[0m";
                } else {
                    std::cout << std::setw(4) << cell;
                }
            }
        }
        std::cout << std::endl;
    }
}

int Board::get_score(int player) {
    int sum = 0;
    for(int row = 1; row <= board_size; row++) {
        for (int col = 1; col <= board_size; col++) {
            sum += (log[row][col] == player ? get_cell(row, col) : 0);
        }
    }

    return sum;
}

int Board::get_size() const {
    return board_size;
}

int Board::is_empty(int row, int col) const {
    return log[row][col] == EMPTY_CELL;
}


bool Board::can_put_card(int row, int col) {
    return log[row][col] == EMPTY_CELL;
}

int Board::get_largest_card(int player) {
    int res = 0;
    for(int row = 1; row <= board_size; row++) {
        for (int col = 1; col <= board_size; col++) {
            if(log[row][col] == player) res = std::max(res, get_cell(row, col));
        }
    }

    return res;
}

int Board::num_empty() const {
    int res = 0;
    for(int row = 1; row <= board_size; row++) {
        for (int col = 1; col <= board_size; col++) {
            if (is_empty(row, col)) res++;
        }
    }
    return res;
}
