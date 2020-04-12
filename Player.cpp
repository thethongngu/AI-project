//
// Created by thong on 4/12/20.
//

#include <iostream>
#include "Player.h"

Player::Player() {}

void Player::reset(bool human, int board_size) {
    this->is_human = human;
    reset_card(board_size);
}

void Player::reset_card(int board_size) {
    if (board_size == 4) {
        cards[0] = 2;  cards[1] = 3; cards[2] = 5; cards[3] = 8; cards[4] = 13;
        num_card = 5;
    } else {
        cards[0] = cards[1] = 2;
        cards[2] = cards[3] = 3;
        cards[4] = cards[5] = 5;
        cards[6] = cards[7] = cards[8] = 8;
        cards[9] = cards[10] = 13;
        num_card = 11;
    }
}

int Player::get_num_card() const {
    return num_card;
}

void Player::print_card() {
    std::cout << "[" << (is_human ? "User" : "AI") << " chess pieces]: [";
    for(int i = 0; i < num_card - 1; i++) {
        std::cout << int(cards[i]) << ", ";
    }
    std::cout << int(cards[num_card - 1]) << "]" << std::endl;
}

void Player::remove_card(int val) {
    for(int i = 0; i < num_card; i++) {
        if (cards[i] == val) {
            cards[i] = cards[num_card - 1];
            cards[num_card - 1] = 0;
        }
    }
    num_card--;
}

void Player::make_move(int &row, int &col, int &val) {
    row = 2;
    col = 3;
    val = 13;

    remove_card(val);
}
