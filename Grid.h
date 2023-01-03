#ifndef SNAKEGAME_GRID_H
#define SNAKEGAME_GRID_H

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <cstdio>

enum class CellType {
    Empty,
    Snake,
    Fruit
};

struct Cell {
    CellType cellType;
    int x;
    int y;
};

class Grid {
private:
    std::vector <std::vector<Cell>> cells;
    int width;
    int height;
    std::mutex mutex;

public:
    Grid(int width, int height);
    Cell& operator()(int x, int y);
    const Cell& operator()(int x, int y) const;
    void clear();
    void draw();

    int getWidth() const;
    void setWidth(int width);
    int getHeight() const;
    void setHeight(int height);
};

#endif //SNAKEGAME_GRID_H
