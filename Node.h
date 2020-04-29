//
// Created by thong on 4/19/20.
//

#ifndef MAIN_NODE_H
#define MAIN_NODE_H


#include <vector>
#include "Board.h"
#include "Player.h"

class Node {
private:
    Board board;
    Player human;
    Player ai;
    int last_row, last_col, last_val;
    int score;
    std::vector<Node> children;

public:
    Node(Board x, Player human, Player ai);

    Player& get_human();
    Player& get_ai();
    Board& get_board();
    bool is_terminal();

    void update_last_move(int row, int col, int val);
    void generate_children(bool is_user_turn);

    int search_ab(int curr_depth, int max_depth, int is_user_turn, int alpha, int beta);
    void get_best_move(int &row, int &col, int &val);
    int eval();
};


#endif //MAIN_NODE_H
