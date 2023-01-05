#include "Game.h"

#include <thread>
#include <mutex>
#include <cstdlib>
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
    //grid.draw();
}

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
//    std::string final_text = "";
    while (true) {

        snake1.move();
        snake2.move();
        std::string screen = grid.draw();

        write(snake2.getSocket() ,screen.c_str() , screen.size() + 1); // posielanie obrazovky na klienta
        usleep(1000);
        write(snake2.getSocket() ,grid.getFinalText().c_str() , grid.getFinalText().size() + 1); // posielanie finalnej spravy na klienta


        if(grid.isGameOver()) {
            std::cout << grid.getFinalText() << std::endl;
            std::exit(0);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }

}

void Game::inputHandler(Snake &snake, Grid &grid) {
    while (!grid.isGameOver()) {
        char c = clientHandler(snake.getPlayerNum(), snake.getSocket());
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
                if (grid.isGameOver()) {
                    snake.getMutex().lock();
                    if (snake.getPlayerNum() == 1) {
//                    snake.setFinalText("Player 1 terminated the game.");
                        grid.setFinalText("Player 1 terminated the game.");
//                    final_text = "Player 1 terminated the game.";
                    } else {
                        grid.setFinalText("Player 2 terminated the game.");
//                    snake.setFinalText("Player 2 terminated the game.");
//                    final_text = "Player 2 terminated the game.";
                    }
//                std::cout << snake.getFinalText() << std::endl;
                    //std::cout << grid.getFinalText() << std::endl;
                    // std::cout << "Press x to end a game :)" << std::endl;
//                std::exit(0);

                    grid.setGameOver(true);
                    snake.getMutex().unlock();
                }

                break;
        }
    }
}


// vstup WASD od klienta/servera
char Game::clientHandler(int playerNum, int socket) {
    char c;
    std::string s;
    if (playerNum == 1) {
        std::cin >> s;
    } else {
        //ak nepojde skuste string buffer
        char buffer[BUFFER_LENGTH + 1];
        buffer[BUFFER_LENGTH] = '\0';
        bzero(buffer, BUFFER_LENGTH);
        read(socket, buffer, BUFFER_LENGTH);
        s = buffer;
        s.pop_back();
    }
    c = s[s.length() - 1]; // posledny char v stringu
    return c;
}

//void Game::send( Grid& grid,Snake& snake2) {
//    std::vector <std::vector<Cell>> cells = grid.getCells();
//    write(snake2.getSocket() ,&cells , grid.getCellsSize());
//}