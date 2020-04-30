//
// Created by thong on 4/12/20.
//

#include <iostream>
#include "Game.h"
#include "global.h"

Game::Game(int is_user, int board_size) :
        board{board_size}, human{true, board_size}, ai{false, board_size} {

    this->is_user_first = is_user;
    this->board_size = board_size;
}

void Game::start(bool autoplay) {
    int row, col, val;

    print_game();
    do {
        if (is_user_first == 1) {
            std::cout << "Input (row, col, weight): ";  std::cin >> row >> col >> val;
            std::cout << "[\033[1;31mUser\033[0m]: (" << row << ", " << col << ", " << val << ")" << std::endl;
            if (!validate_user_input(row, col, val) || !board.put_card(row, col, val, HUMAN_CELL)) {
                std::cout << "Illegal move. Please try again!" << std::endl;
                continue;
            }
            human.remove_card(val);
        } else {
            float max_score = Player::make_move(board, human, ai, row, col, val);
            board.put_card(row, col, val, AI_CELL);
            ai.remove_card(val);
            std::cout << "[\033[1;32mAI\033[0m]: (" << row << ", " << col << ", " << val << ")" << std::endl;

            if (max_score == MAX) {
                std::cout << "Spoiler: I will win :D" << std::endl;
            }
        }

        board.check_all();
        print_game();
        is_user_first = 1 - is_user_first;

    } while (!end_game());

    int human_score, ai_score, human_card, ai_card;
    int res = get_result(human_score, ai_score, human_card, ai_card);
    std::string s = (res == 1) ? "\033[1;32mAI\033[0m win!" : "\033[1;31mUser\033[0m win!";

    std::cout << s << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\033[1;31mUser score\033[0m (score, largest card): " << human_score << " " << human_card << std::endl;
    std::cout << "\033[1;32mAI score\033[0m   (score, largest card): " << ai_score << " " << ai_card << std::endl;
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

bool Game::validate_user_input(int row, int col, int val) {
    if (row < 1 || row > board_size) return false;
    if (col < 1 || col > board_size) return false;
    return human.has_card(val);
}

int Game::get_result(int &human_score, int &ai_score, int &human_card, int &ai_card) {
    board.get_score(HUMAN_CELL, human_score, human_card);
    board.get_score(AI_CELL, ai_score, ai_card);
    return Board::check_ai_win(human_score, human_card, ai_score, ai_card);
}
