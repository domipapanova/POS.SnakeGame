#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME_SNAKE_H

#include "Grid.h"
#include "Consts.h"

class Snake {
private:
    std::vector<Cell> body;
    Grid &grid;
    std::mutex &mutex;

    int dx;
    int dy;
    int playerNum;
    int socket;
    CellType cellTypeHead;
    CellType cellTypeSnake;

public:
    Snake(Grid &grid, std::mutex &mutex, int x, int y, int playerNum);
    ~Snake();

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
    CellType getCellTypeHead() const;
    CellType getCellTypeSnake() const;
};

#endif //SNAKEGAME_SNAKE_H
