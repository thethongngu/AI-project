//
// Created by thong on 4/12/20.
//

#include "Board.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

unsigned char Board::EMPTY = 2;

Board::Board() {
    this->board_size = 0;
}

bool Board::put_card(int row, int col, int val, int player) {
    if (log[row][col] != EMPTY) return false;
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

void Board::reset(int size) {
    this->board_size = size;
    for(int row = 1; row <= board_size; row++) {
        for (int col = 1; col <= board_size; col++) {
            grid[row][col] = 0;
            log[row][col] = EMPTY;
        }
    }
}

int Board::get_cell(int row, int col) {
    return (int) grid[row][col];
}

void Board::print_board() {
    for(int row = 1; row <= board_size; row++) {
        for(int col = 1; col <= board_size; col++) {
            int cell = get_cell(row, col);
            char val = (log[row][col] != EMPTY && cell == 0) ? val = 'X' : val = '0';
            std::cout << std::setw(4) << val;
        }
        std::cout << std::endl;
    }
}

int Board::get_score(int player) {
    int sum = 0;
    for(int row = 1; row < board_size; row++) {
        for (int col = 1; col < board_size; col++) {
            sum += (log[row][col] == player ? grid[row][col] : 0);
        }
    }

    return sum;
}

int Board::get_size() {
    return board_size;
}
