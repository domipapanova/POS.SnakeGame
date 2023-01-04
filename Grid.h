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
public:


private:
    int width;
    int height;
    std::mutex mutex; // mozno & by malo byt

public:
    Grid(int width, int height);
    Cell& operator()(int x, int y);
    const Cell& operator()(int x, int y) const;
    void clear();
    std::string draw();

    int getWidth() const;
    int getHeight() const;
//    std::vector<std::vector<Cell>> &getCells();
//    int getCellsSize() const;
};

#endif //SNAKEGAME_GRID_H
