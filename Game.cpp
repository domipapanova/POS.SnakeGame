#include "Game.h"
#include <thread>

// new game with the given dimensions
Game::Game(int width, int height)
    : grid(width, height), snake1(grid, mutex, width/2, height/3, 1),
      snake2(grid, mutex, width/2, height/3 * 2, 2) {   // snakes spawn in the middle of the grid
    grid.clear();
    snake1.spawnFruit();
    snake2.spawnFruit();
    //grid.draw();
}

// create the players and update threads
void Game::start() {
    player1Thread = std::thread(&Game::inputHandler, std::ref(snake1));
    player2Thread = std::thread(&Game::inputHandler, std::ref(snake2));
    updateThread = std::thread(&Game::update, std::ref(grid), std::ref(snake1), std::ref(snake2));
}

// stop the players and update threads
void Game::stop() {
    player1Thread.join();
    player2Thread.join();
    updateThread.join();
}


void Game::update(Grid& grid, Snake& snake1, Snake& snake2) {
    while (true) {
        snake1.move();
        snake2.move();
        grid.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
}

void Game::inputHandler(Snake& snake) {
    while (true) {
        std::string s;
        std::cin >> s;
        char c = s[s.length() - 1];
        switch (c) {
            case 'w':
            case 'i':
                snake.getMutex().lock();
                if (snake.getDy() != 1) {
                    snake.setDx(0);
                    snake.setDy(-1);
                }
                snake.getMutex().unlock();
                break;
            case 'a':
            case 'j':
                snake.getMutex().lock();
                if (snake.getDx() != 1) {
                    snake.setDx(-1);
                    snake.setDy(0);
                }
                snake.getMutex().unlock();
                break;
            case 's':
            case 'k':
                snake.getMutex().lock();
                if (snake.getDy() != -1) {
                    snake.setDx(0);
                    snake.setDy(1);
                }
                snake.getMutex().unlock();
                break;
            case 'd':
            case 'l':
                snake.getMutex().lock();
                if (snake.getDx() != -1) {
                    snake.setDx(1);
                    snake.setDy(0);
                }
                snake.getMutex().unlock();
                break;
            case 'x':
                std::cout << "Player " << snake.getPlayerNum() <<" terminated the game." << std::endl;
                std::exit(0);
        }
    }
}
