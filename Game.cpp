#include "Game.h"
#include <thread>
#include <pthread.h>

// new game with the given dimensions
Game::Game(int width, int height)
    : grid(width, height), snake(grid, mutex, width/2, height/2){   // snake spawn in the middle of the screen

    grid.clear();
    snake.spawnFruit();
    //grid.draw();
}

void Game::start() {
    // create the input and update threads
    inputThread = std::thread(&Game::inputHandler, std::ref(snake));
    updateThread = std::thread(&Game::update, std::ref(grid), std::ref(snake));

//    pthread_t inputThread;
//    pthread_create(&inputThread, NULL, &Game::inputHandler, &snake)

}

void Game::stop() {
    // stop the input and update threads
    inputThread.join();
    updateThread.join();
}


void Game::update(Grid& grid, Snake& snake) {
    while (true) {
        snake.move();
        grid.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
}

void Game::inputHandler(Snake& snake) {
//    std::lock_guard<std::mutex> lock(snake.getMutex());
    while (true) {
        char c = std::cin.get();

        switch (c) {
            case 'w':
                snake.getMutex().lock();
                if (snake.getDy() != 1) {
                    snake.setDx(0);
                    snake.setDy(-1);
                }
                snake.getMutex().unlock();
                break;
            case 'a':
                snake.getMutex().lock();
                if (snake.getDx() != 1) {
                    snake.setDx(-1);
                    snake.setDy(0);
                }
                snake.getMutex().unlock();
                break;
            case 's':
                snake.getMutex().lock();
                if (snake.getDy() != -1) {
                    snake.setDx(0);
                    snake.setDy(1);
                }
                snake.getMutex().unlock();
                break;
            case 'd':
                snake.getMutex().lock();
                if (snake.getDx() != -1) {
                    snake.setDx(1);
                    snake.setDy(0);
                }
                snake.getMutex().unlock();
                break;
        }
    }
}
