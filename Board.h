//
// Created by thong on 4/12/20.
//

#ifndef AI_BOARD_H
#define AI_BOARD_H


class Board {
private:

    unsigned char grid[8][8] = {0};
    unsigned char board_size;

public:
    Board(int board_size);

    bool check_at(int row, int col);
    void check_all();
    bool put_card(int row, int col, int val);

};


#endif //AI_BOARD_H
