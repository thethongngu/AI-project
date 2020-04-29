//
// Created by thong on 4/12/20.
//

#include <iostream>
#include "Game.h"

int main() {

    int is_user_first, board_size;

    std::cout << "User first(0/1): ";
    std::cin >> is_user_first;
    std::cout << "Board size? (4 or 6): ";
    std::cin >> board_size;

    Game game(is_user_first, board_size);
    game.start(false);
}

