#include "Game.h"
#include <iostream>

int main () {
    srand(time(NULL));
    Game* game = new Game(12, 8);
    game->start();
    game->stop();
    delete game;

}

