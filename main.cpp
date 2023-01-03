#include "Grid.h"
#include "Game.h"
#include "Snake.h"

#include <iostream>
#include <cstring>

int main () {
    Game* game = new Game(10, 10);
    game->start();
    game->stop();
    return 0;
}

