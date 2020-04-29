//
// Created by thong on 4/12/20.
//

#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H


#include "Board.h"

class Player {
private:
    int cards[11]{};
    int num_card{};
    bool is_human;

public:
    Player(bool is_human, int board_size);


    void reset_card(int board_size);
    unsigned char get_card(int card_id);
    int get_num_card() const;
    bool has_card(int val);
    void print_card();
    void remove_card(int val);
    int sum_cards();

    static int estimate_max_depth(const Board& board, const Player& human, const Player& ai);
    static int make_move(const Board& board, const Player& human, const Player& ai, int &row, int &col, int&val);
};


#endif //MAIN_PLAYER_H
