//
// Created by thong on 4/12/20.
//

#ifndef MAIN_GAME_H
#define MAIN_GAME_H


#include "Board.h"
#include "Player.h"

class Game {
private:
    int turn;
    int board_size;

    Board board;
    Player human, ai;
    int human_score, ai_score;

public:
    Game();

    void start();
    bool end_game();
    void print_game();
};


#endif //MAIN_GAME_H