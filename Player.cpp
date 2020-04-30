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

int Player::get_num_card() const {
    return num_card;
}

void Player::print_card() {
    std::cout << "[" << (is_human ? "\033[1;31mUser chess pieces\033[0m]: [" : "\033[1;32mAI chess pieces\033[0m  ]: [");
    for(int i = 0; i < num_card - 1; i++) {
        std::cout << cards[i] << ", ";
    }
    if (num_card != 0) std::cout << cards[num_card - 1];
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

float Player::make_move(const Board &board, const Player &human, const Player &ai, int &row, int &col, int &val) {
    Node root(board, human, ai);
    int max_depth = estimate_max_depth(board, human, ai);
//    debug(max_depth);
    float max_score = root.search_ab(0, max_depth, false, MIN, MAX);
//    debug(max_score);
    root.get_best_move(row, col, val);

    return max_score;
}

int Player::get_card(int card_id) {
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

int Player::estimate_max_depth(const Board &board, const Player &human, const Player &ai) {
    int num_empty = board.num_empty();
    int num_ai = ai.get_num_card();
    int num_human = human.get_num_card();
    int num_node = 1, depth = 0, turn = 0;

    do {
        depth++;
        if (turn == 0) {
            num_node *= num_empty * std::min(5, num_ai);
            num_ai--;
        } else {
            num_node *= num_empty * std::min(5, num_human);
            num_human--;
        }
        num_empty--;
        turn = 1 - turn;
    } while (num_node <= MAX_NODE && num_empty > 0 && num_ai + num_human > 0);

    return (depth % 2 == 0) ? std::max(3, depth - 1): std::max(3, depth);
}
