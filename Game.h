//
// Created by thong on 4/12/20.
//

#ifndef MAIN_GAME_H
#define MAIN_GAME_H


#include "Board.h"
#include "Player.h"

class Game {
private:
    int is_user;
    int board_size;

    Board board;
    Player human, ai;
    int human_score, ai_score;

public:
    Game(int is_user, int board_size);

    void start();
    bool end_game();
    void print_game();
    bool validate_user_input(int row, int col, int val);
};


#endif //MAIN_GAME_H
