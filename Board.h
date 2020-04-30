//
// Created by thong on 4/12/20.
//

#ifndef AI_BOARD_H
#define AI_BOARD_H


class Board {
private:

    int grid[8][8];  // card value
    int log[8][8];   // card player
    int board_size;

public:
    explicit Board(int size);

    void reset();

    int get_size() const;
    int get_cell(int row, int col);
    int is_empty(int row, int col) const;
    int num_empty() const;

    bool check_at(int row, int col);
    void check_all();
    static int check_ai_win(int human_score, int human_card, int ai_score, int ai_card);
    bool can_put_card(int row, int col);

    bool put_card(int row, int col, int val, int player);
    void print_board();

    void get_score(int player, int &board_score, int &card_score);
    void get_removing_info(int row, int col, int &remain_cell, int &remain_score);
};


#endif //AI_BOARD_H
