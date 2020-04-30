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
    for(int i = 0; i < 9; i++) {
        sum += grid[row + x[i]][col + y[i]];
    }
    return sum <= 15;
}

void Board::check_all() {
    std::pair<int, int> remove[64];
    int len = 0;
    for(int row = 1; row <= board_size; row++) {
        for (int col = 1; col <= board_size; col++) {
            if (!check_at(row, col)) remove[len++] = std::pair<int, int>(row, col);
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

    std::cout << std::endl << "       |" << std::setw(4) << 1;
    for(int i = 2; i <= board_size; i++) std::cout << std::setw(4) << i;
    std::cout << std::endl;
    std::cout << "----------------------------------" << std::endl;

    for(int row = 1; row <= board_size; row++) {
        std::cout << std::setw(4) << row << "   |";
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

    std::cout << "\n======================================" << std::endl;
}

void Board::get_score(int player, int &board_score, int &card_score) {
    card_score = 0;  board_score = 0;
    for(int row = 1; row <= board_size; row++) {
        for (int col = 1; col <= board_size; col++) {
            if (log[row][col] == player) {
                board_score += get_cell(row, col);
                card_score = std::max(card_score, get_cell(row, col));
            }
        }
    }
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

int Board::num_empty() const {
    int res = 0;
    for(int row = 1; row <= board_size; row++) {
        for (int col = 1; col <= board_size; col++) {
            if (is_empty(row, col)) res++;
        }
    }
    return res;
}

int Board::check_ai_win(int human_score, int human_card, int ai_score, int ai_card) {
    if (human_score > ai_score) return -1;
    if (human_score == ai_score && human_card > ai_card) return -1;
    if (human_score == ai_score && human_card == ai_card) return 0;
    return 1;
}


