//
// Created by thong on 4/19/20.
//

#include "Node.h"

Node::Node() {

}

void Node::reset(Board x) {
    board = x;
    human.reset(true, board.get_size());
    ai.reset(false, board.get_size());
    children.clear();
}

bool Node::is_terminal() {
    return human.get_num_card() == 0 && ai.get_num_card() == 0;
}

int Node::eval() {
    return 0;
}

int Node::search_ab(Node node, int depth, int curr_depth, int alpha, int beta, int turn, int &row, int &col, int &val) {

    if (curr_depth == depth || node.is_terminal()) {
        return node.eval();
    }

    if (turn == 0) {  // ai moves, maximizing
        int value = -1000000000;
        for(const auto& child: children) {
            value = std::max(value, search_ab(child, depth, curr_depth++, alpha, beta, 1 - turn, row, col, val));
            alpha = std::max(alpha, value);
            if (alpha >= beta) break;
        }
        return value;
    } else {  // human moves, minimizing
        int value = 1000000000;
        for(const auto& child: children) {
            value = std::min(value, search_ab(child, depth, curr_depth++, alpha, beta, 1 - turn, row, col, val));
            beta = std::min(beta, value);
            if (alpha >= beta) break;
        }
        return value;
    }
}


