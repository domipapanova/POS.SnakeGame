#include "Grid.h"

Grid::Grid(int width, int height, std::mutex &mutex)
    : width(width), height(height), mutex(mutex) {
    final_text = "";
    gameOver = false;
    cells.resize(height);
    for (auto& row : cells) {
        row.resize(width);
    }
}

Grid::~Grid() {
    width = 0;
    height = 0;
    final_text = "";
    // mozno vektory
}


// return the cell at the given position
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
std::string Grid::draw() {
    std::lock_guard<std::mutex> lock(mutex);
    std::string screen;
    for (int y = 0; y < height; y++) {
        std::cout << "|"; // edges are not being sent to the client

        for (int x = 0; x < width; x++) {
            switch (cells[y][x].cellType) {
                case CellType::Empty:
                    std::cout << " ";
                    screen += " ";
                    break;
                case CellType::Snake:
                    std::cout << "o";
                    screen += "o";
                    break;
                case CellType::Fruit:
                    std::cout << "x";
                    screen += "x";
                    break;
                case CellType::Head:
                    std::cout << "O";
                    screen += "O";
                    break;
            }
        }
        std::cout << "|";
        std::cout << std::endl;
    }
    std::cout << "\n\n\n" << std::endl;
    return screen;
}

int Grid::getWidth() const {
    return width;
}

int Grid::getHeight() const {
    return height;
}

const std::string &Grid::getFinalText() const {
    return final_text;
}

void Grid::setFinalText(const std::string &finalText) {
    final_text = finalText;
}

bool Grid::isGameOver() const {
    return gameOver;
}

void Grid::setGameOver(bool gameOver) {
    Grid::gameOver = gameOver;
}





