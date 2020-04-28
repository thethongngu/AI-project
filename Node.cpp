//
// Created by thong on 4/19/20.
//

#include "Node.h"
#include "global.h"

Node::Node(Board x, Player human, Player ai, int max_depth)
        : board{x}, human{human}, ai{ai}, max_depth{max_depth}, last_col(-1), last_row(-1), last_val(-1), score(0) {}

bool Node::is_terminal() {
    return human.get_num_card() == 0 && ai.get_num_card() == 0;
}

int Node::eval() {
    return 0;
}

int Node::search_ab(int curr_depth, int is_user_turn, int alpha, int beta) {

    get_board().print_board();
    if (curr_depth == max_depth || is_terminal()) return eval();

    generate_children(is_user_turn);

    if (!is_user_turn) {  // ai moves, maximizing
        score = MAX;
        for(auto& child: children) {
            score = std::max(score, child.search_ab(curr_depth++, !is_user_turn, alpha, beta));
            alpha = std::max(alpha, score);
            if (alpha >= beta) break;
        }
        return score;

    } else {  // human moves, minimizing
        score = MIN;
        for(auto& child: children) {
            score = std::min(score, child.search_ab(curr_depth++, !is_user_turn, alpha, beta));
            beta = std::min(beta, score);
            if (alpha >= beta) break;
        }
        return score;
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
                    last_row = i;  last_col = j;  last_val = card;
                    child.get_human().remove_card(card);
                    children.push_back(child);
                }
            }
            else {
                for(int card_id = 0; card_id < ai.get_num_card(); card_id++) {
                    unsigned char card = ai.get_card(card_id);
                    Node child(board, human, ai, max_depth - 1);
                    child.get_board().put_card(i, j, card, AI_CELL);
                    last_row = i;  last_col = j;  last_val = card;
                    child.get_ai().remove_card(card);
                    children.push_back(child);
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

void Node::get_best_move(int &row, int &col, int &val) {
    int best_val = 0;
    for(const Node& child: children) {
        if (child.score > best_val) {
            best_val = child.score;
            row = child.last_row;
            col = child.last_col;
            val = child.last_val;
        }
    }
}


