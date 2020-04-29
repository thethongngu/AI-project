//
// Created by thong on 4/12/20.
//

#include <iostream>
#include "Player.h"
#include "Node.h"
#include "global.h"

Player::Player(bool human, int board_size) : is_human(human) {
    reset_card(board_size);
}

void Player::reset_card(int board_size) {
    if (board_size == 4) {
        cards[0] = 2;  cards[1] = 3; cards[2] = 5;
        cards[3] = 8;  cards[4] = 13;
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

int Player::get_num_card() {
    return num_card;
}

void Player::print_card() {
    std::cout << "[" << (is_human ? "\033[1;31mUser chess pieces\033[0m]: [" : "\033[1;32mAI chess pieces\033[0m]: [");
    for(int i = 0; i < num_card - 1; i++) {
        std::cout << int(cards[i]) << ", ";
    }
    if (num_card != 0) std::cout << int(cards[num_card - 1]);
    std::cout << "]" << std::endl;
}

void Player::remove_card(int val) {
    if (num_card == 1) {
        cards[0] = 0;
        num_card = 0;
        return;
    }
    for(int i = 0; i < num_card; i++) {
        if (cards[i] == val) {
            cards[i] = cards[num_card - 1];
            cards[num_card - 1] = 0;
            break;
        }
    }
    num_card--;
}

void Player::make_move(const Board &board, const Player &human, const Player &ai, int &row, int &col, int &val) {
    Node root(board, human, ai);
    root.search_ab(0, false, MIN, MAX);
    root.get_best_move(row, col, val);
}

unsigned char Player::get_card(int card_id) {
    return cards[card_id];
}

bool Player::has_card(int val) {
    for(int i = 0; i < num_card; i++)
        if (cards[i] == val) return true;
    return false;
}

int Player::sum_cards() {
    int res = 0;
    for(int i = 0; i < num_card; i++) res += cards[i];
    return res;
}
