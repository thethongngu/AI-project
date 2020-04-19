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
    std::vector<Node> children;

public:
    Node();
    void reset(Board x);
    int search_ab(Node node, int depth, int curr_depth, int turn, int alpha, int beta, int &row, int &col, int &val);
    bool is_terminal();
    int eval();
};


#endif //MAIN_NODE_H
