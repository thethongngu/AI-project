//
// Created by thong on 4/12/20.
//

#include "Board.h"
#include <cassert>
#include <algorithm>

Board::Board(int board_size) {
    this->board_size = board_size;
}

bool Board::put_card(int row, int col, int val) {
    if (grid[row][col] != 0) return false;
    grid[row][col] = val;
    return true;
}

bool Board::check_at(int row, int col) {
    char x[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    char y[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

    int sum = 0;
    for(unsigned char i = 0; i < 9; i++) {
        sum += std::max((unsigned char)0, grid[row + x[i]][col + y[i]]);
    }
    return sum <= 15;
}

void Board::check_all() {
    std::pair<unsigned char, unsigned char> remove[64];
    int len = 0;
    for(unsigned char row = 1; row <= board_size; row++) {
        for (unsigned char col = 1; col <= board_size; col++) {
            if (!check_at(row, col)) remove[len++] = std::pair<unsigned char, unsigned char>(row, col);
        }
    }

    for(int i = 0; i < len; i++) {
        auto pos = remove[i];
        grid[pos.first][pos.second] = -1;
    }
}
