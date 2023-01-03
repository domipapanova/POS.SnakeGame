#include "Grid.h"
#include "Game.h"
#include "Snake.h"

#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>


int main () {
    srand(time(NULL));

    Game* game = new Game(10, 5);
    game->start();
    game->stop();
    delete game;

}

