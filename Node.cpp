//
// Created by thong on 4/19/20.
//

#include "Node.h"
#include "global.h"

Node::Node(Board x, Player human, Player ai, int max_depth)
        : board{x}, human{human}, ai{ai}, max_depth{max_depth} {}

bool Node::is_terminal() {
    return human.get_num_card() == 0 && ai.get_num_card() == 0;
}

int Node::eval() {
    return 0;
}

int Node::search_ab(int curr_depth, int is_user_turn, int alpha, int beta, int &row, int &col, int &val) {

    if (curr_depth == max_depth || is_terminal()) return eval();

    generate_children(!is_user_turn);

    if (!is_user_turn) {  // ai moves, maximizing
        int value = -1000000000;
        for(const auto& child: children) {
            value = std::max(value, search_ab(curr_depth++, !is_user_turn, alpha, beta, row, col, val));
            alpha = std::max(alpha, value);
            if (alpha >= beta) break;
        }
        return value;
    } else {  // human moves, minimizing
        int value = 1000000000;
        for(const auto& child: children) {
            value = std::min(value, search_ab(curr_depth++, !is_user_turn, alpha, beta, row, col, val));
            beta = std::min(beta, value);
            if (alpha >= beta) break;
        }
        return value;
    }
}

void Node::generate_children(bool is_user_turn) {

    for(int i = 1; i <= board.get_size(); i++) {
        for(int j = 1; j <= board.get_size(); j++) {
            if (!board.can_put_card(i, j)) continue;

            if (is_user_turn) {
                for(int card_id = 0; card_id < human.get_num_card(); card_id++) {
                    unsigned char card = human.get_card(card_id);
                    Node child(board, human, ai, max_depth - 1);
                    child.get_board().put_card(i, j, card, HUMAN_CELL);
                    child.get_human().remove_card(card);
                }
            }
            else {
                for(int card_id = 0; card_id < ai.get_num_card(); card_id++) {
                    unsigned char card = ai.get_card(card_id);
                    Node child(board, human, ai, max_depth - 1);
                    child.get_board().put_card(i, j, card, AI_CELL);
                    child.get_ai().remove_card(card);
                }
            }
        }
    }
}

Player &Node::get_human() {
    return human;
}

Player &Node::get_ai() {
    return ai;
}

Board &Node::get_board() {
    return board;
}


