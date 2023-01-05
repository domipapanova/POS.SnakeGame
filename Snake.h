#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME_SNAKE_H

#include "Grid.h"
#define WINNING_SIZE 15

class Snake {
private:
    std::vector<Cell> body;
    Grid &grid;
    std::mutex &mutex;
    int dx;
    int dy;
    int playerNum;
    int socket;

public:
    Snake(Grid &grid, std::mutex &mutex, int x, int y, int playerNum);
    void move();
    void spawnFruit();
    int getDx() const;
    void setDx(int dx);
    int getDy() const;
    void setDy(int dy);
    std::mutex &getMutex() const;
    int getPlayerNum() const;
    int getSocket() const;
    void setSocket(int pSocket);
};

#endif //SNAKEGAME_SNAKE_H
