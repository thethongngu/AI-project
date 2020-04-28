//
// Created by thong on 4/12/20.
//

#include <iostream>
#include "Game.h"
#include "global.h"

Game::Game(int is_user, int board_size) :
        board{board_size}, human{true, board_size}, ai{false, board_size} {

    this->is_user = is_user;
    this->board_size = board_size;
    this->human_score = this->ai_score = 0;
}

void Game::start() {
    int row, col, val;

    print_game();
    do {
        if (is_user == 1) {
            std::cout << "Input (row, col, weight): ";  std::cin >> row >> col >> val;
            std::cout << "[\033[1;31mUser\033[0m]: (" << row << ", " << col << ", " << val << ")" << std::endl;
            if (!board.put_card(row, col, val, HUMAN_CELL)) {
                std::cout << "Illegal move. Please try again!" << std::endl;
                continue;
            }
            human.remove_card(val);
        } else {
            ai.make_move(board, human, ai, row, col, val);
            board.put_card(row, col, val, AI_CELL);
            ai.remove_card(val);
            std::cout << "[\033[1;32mAI\033[0m]: (" << row << ", " << col << ", " << val << ")" << std::endl;
        }

        board.check_all();
        print_game();
        is_user = 1 - is_user;

    } while (!end_game());
}

void Game::print_game() {
    board.print_board();
    std::cout << std::endl;

    human.print_card();
    ai.print_card();
    std::cout << std::endl;
}

bool Game::end_game() {
    return human.get_num_card() == 0 && ai.get_num_card() == 0;
}