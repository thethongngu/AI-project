//
// Created by thong on 4/12/20.
//

#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H


#include "Board.h"

class Player {
private:
    unsigned char cards[11];
    unsigned char num_card;
    bool is_human;

public:
    Player(bool is_human, int board_size);

    void reset_card(int board_size);
    unsigned char get_card(int card_id);
    int get_num_card() const;
    void print_card();
    void remove_card(int val);

    void make_move(const Board& board, const Player& human, const Player& ai, int &row, int &col, int&val);
};


#endif //MAIN_PLAYER_H
