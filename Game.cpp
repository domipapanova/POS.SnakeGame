#include "Game.h"
#include <thread>
#include <mutex>
#include <cstring>
#include <unistd.h>
#include <iostream>

// new game with the given dimensions
Game::Game(int width, int height, int clientSocket)
    : grid(width, height, mutex), snake1(grid, mutex, width/2, height/3, 1),
      snake2(grid, mutex, width/2, height/3 * 2, 2) {   // snakes spawn in the middle of the grid
    grid.clear();
    snake2.setSocket(clientSocket);
    snake1.spawnFruit();
    snake2.spawnFruit();
}

Game::~Game() = default;

// create the players and update threads
void Game::start() {
    player1Thread = std::thread(&Game::inputHandler, std::ref(snake1), std::ref(grid));
    player2Thread = std::thread(&Game::inputHandler, std::ref(snake2), std::ref(grid));
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
        std::string screen = grid.draw();

        write(snake2.getSocket() ,screen.c_str() , screen.size() + 1); // sending screen to client
        usleep(3000);
        write(snake2.getSocket() ,grid.getFinalText().c_str() , grid.getFinalText().size() + 1); // sending final message to client

        if(grid.isGameOver()) {
            std::cout << grid.getFinalText() << std::endl;
            std::cout << "Press x to end the game :)" << std::endl;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void Game::inputHandler(Snake &snake, Grid &grid) {
    while (!grid.isGameOver()) {
        char c = clientHandler(snake.getPlayerNum(), snake.getSocket());
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
            case 'x':
                    snake.getMutex().lock();
                    if (snake.getPlayerNum() == 1) {
                        grid.setFinalText("Player 1 terminated the game.");
                    } else {
                        grid.setFinalText("Player 2 terminated the game.");
                    }
                    grid.setGameOver(true);
                    snake.getMutex().unlock();
                    break;
        }
    }
}

// WASD input from client/server
char Game::clientHandler(int playerNum, int socket) {
    char c;
    std::string s;
    if (playerNum == 1) {
        // WASD input from server
        std::cin >> s;
    } else {
        // WASD input from client
        char buffer[BUFFER_LENGTH + 1];
        buffer[BUFFER_LENGTH] = '\0';
        bzero(buffer, BUFFER_LENGTH);
        read(socket, buffer, BUFFER_LENGTH);
        s = buffer;
        s.pop_back();
    }
    c = s[s.length() - 1]; // last character of the string
    return c;
}