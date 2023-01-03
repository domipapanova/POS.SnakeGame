#ifndef SNAKEGAME_GAME_H
#define SNAKEGAME_GAME_H

#include "Grid.h"
#include "Snake.h"

class Game {
private:
    Grid grid;
    Snake snake;
    std::mutex mutex;
    std::thread inputThread;
    std::thread updateThread;
public:
    Game(int width, int height);
    void start();
    void stop();
    static void inputHandler(Snake& snake);
    static void update(Grid& grid, Snake& snake);
};


#endif //SNAKEGAME_GAME_H
