#include "Grid.h"
#include "Game.h"
#include "Snake.h"

#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>


int main () {
    srand(time(NULL));

//    sf::RenderWindow window(sf::VideoMode(800, 600), "SnakeGame");
    Game* game = new Game(10, 5);
    game->start();
    game->stop();
    delete game;


//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//
//        window.display();
//    }
}

