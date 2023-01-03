#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME_SNAKE_H

#include "Grid.h"


class Snake {
private:
    std::vector<Cell> body;
    Grid &grid;
    std::mutex &mutex;
public:
    std::mutex &getMutex() const;

private:
    int dx;
    int dy;

public:
    Snake(Grid &grid, std::mutex &mutex, int x, int y);
    void move();
    void spawnFruit();

    int getDx() const;
    void setDx(int dx);
    int getDy() const;
    void setDy(int dy);
};

#endif //SNAKEGAME_SNAKE_H
