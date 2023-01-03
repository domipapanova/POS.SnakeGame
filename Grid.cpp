#include "Grid.h"

Grid::Grid(int width, int height)
    : width(width), height(height) {
    cells.resize(height);
    for (auto& row : cells) {
        row.resize(width);
    }
}

// Return the cell at the given position
Cell& Grid::operator()(int x, int y) {
    return cells[y][x];
}

const Cell& Grid::operator()(int x, int y) const {
    return cells[y][x];
}

// clear the grid
void Grid::clear() {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& row : cells) {
        for (auto& cell : row) {
            cell.cellType = CellType::Empty;
        }
    }
}

// draw the grid to the console
void Grid::draw() {
    std::lock_guard<std::mutex> lock(mutex);

    for (int y = 0; y < height; y++) {
        std::cout << "|";

        for (int x = 0; x < width; x++) {
            switch (cells[y][x].cellType) {
                case CellType::Empty:
                    std::cout << " ";
                    break;
                case CellType::Snake:
                    std::cout << "o";
                    break;
                case CellType::Fruit:
                    std::cout << "x";
                    break;
            }
        }
        std::cout << "|";
        std::cout << std::endl;
    }
    std::cout << "\n\n\n" << std::endl;
}

int Grid::getWidth() const {
    return width;
}

int Grid::getHeight() const {
    return height;
}