//
// Created by thong on 4/12/20.
//

#include <iostream>
#include "Game.h"

void Game::start() {
    int row, col, val;

    std::cout << "User first(0/1): ";
    std::cin >> turn;
    std::cout << "Board size? (4 or 6): ";
    std::cin >> board_size;

    board.reset(board_size);
    human.reset(true, board_size);
    ai.reset(false, board_size);
    human_score = ai_score = 0;
    print_game();

    do {
        if (turn % 2 == 1) {
            std::cout << "Input (row, col, weight): ";  std::cin >> row >> col >> val;
            std::cout << "[User]: (" << row << ", " << col << ", " << val << ")" << std::endl;
            human.remove_card(val);
        } else {
            ai.make_move(row, col, val);
            std::cout << "[AI]: (" << row << ", " << col << ", " << val << ")" << std::endl;
        }

        board.put_card(row, col, val, turn);
        board.check_all();

        print_game();
        turn = 1 - turn;

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

Game::Game() {}
