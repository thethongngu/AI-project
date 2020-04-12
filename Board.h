//
// Created by thong on 4/12/20.
//

#ifndef AI_BOARD_H
#define AI_BOARD_H


class Board {
private:

    unsigned char grid[8][8] = {0};  // card value
    unsigned char log[8][8] = {0};   // card player
    unsigned char board_size;

public:
    Board();

    void reset(int size);
    int get_cell(int row, int col);
    bool check_at(int row, int col);
    void check_all();
    bool put_card(int row, int col, int val, int player);
    void print_board();
    int get_score(int player);

    static unsigned char EMPTY;
};


#endif //AI_BOARD_H
