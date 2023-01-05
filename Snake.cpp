#include "Snake.h"
#include <string>

//TODO: odlisit hadiky
Snake::Snake(Grid &grid, std::mutex &mutex, int x, int y, int playerNum): grid(grid), mutex(mutex), playerNum(playerNum){
    body.push_back({CellType::Head, x, y});
    body.push_back({CellType::Snake, x - 1, y});
    body.push_back({CellType::Snake, x - 2, y});
    dx = 1;
    dy = 0;
    socket = 0;
}

void Snake::move() {
//    std::lock_guard<std::mutex> lock(mutex);
    // Remove the tail of the snake
    auto& tail = body.back();
    mutex.lock();
    grid(tail.x, tail.y).cellType = CellType::Empty;

    body.pop_back();

    // Add a new cell to the head of the snake in the direction it is moving
    auto& head = body.front();
    int newX = head.x + dx;
    int newY = head.y + dy;

    // Wrap around the edges of the grid
    if (newX < 0) {
        newX += grid.getWidth();
    }
    if (newX >= grid.getWidth()){
        newX -= grid.getWidth();
    }
    if (newY < 0){
        newY += grid.getHeight();
    }
    if (newY >= grid.getHeight()) {
        newY -= grid.getHeight();
    }

    body.insert(body.begin(), {CellType::Snake, newX, newY});

    // check for collision with fruit
    const Cell newHead = body.front();

    if (grid(newHead.x, newHead.y).cellType == CellType::Fruit) {
        // grow the snake and spawn a new fruit
        body.push_back(tail);

        // check if the player won
        if (body.size() == WINNING_SIZE) {
//            final_text = "Player " + std::to_string(playerNum) + " won!";
            grid.setFinalText("Player " + std::to_string(playerNum) + " won!");
            std::cout << grid.getFinalText() << std::endl;

//            std::exit(0);
            grid.setGameOver(true);
        }

        mutex.unlock();
        spawnFruit();

    } else {
        mutex.unlock();
    }
    // check for collision with snake cells
    if (grid(newHead.x, newHead.y).cellType == CellType::Snake) {
        //TODO: kontrolovat celne zrazky, dlzku hadika a pripadnu remizu
        mutex.lock();
        if (playerNum == 1) {
            grid.setFinalText("Player 2 won!");
        } else {
            grid.setFinalText("Player 1 won!");
        }
        grid.setGameOver(true);
        mutex.unlock();
    }

    // check for collision with head
    if (grid(newHead.x, newHead.y).cellType == CellType::Head) {
        mutex.lock();
        grid.setFinalText("It's a Draw!");
        grid.setGameOver(true);
        mutex.unlock();
    }

    // update the grid
    for (auto& cell : body) {
        mutex.lock();
        grid(cell.x, cell.y).cellType = CellType::Snake;
        mutex.unlock();
    }
}

// find a random empty cell to place the fruit
void Snake::spawnFruit() {
    while (true) {
        int x = rand() % grid.getWidth();
        int y = rand() % grid.getHeight();
        if (grid(x, y).cellType == CellType::Empty) {
            mutex.lock();
            grid(x, y).cellType = CellType::Fruit;
            mutex.unlock();
            break;
        }
    }
}

int Snake::getDx() const {
    return dx;
}

void Snake::setDx(int dx) {
    Snake::dx = dx;
}

int Snake::getDy() const {
    return dy;
}

void Snake::setDy(int dy) {
    Snake::dy = dy;
}

std::mutex &Snake::getMutex() const {
    return mutex;
}

int Snake::getPlayerNum() const {
    return playerNum;
}

void Snake::setSocket(int pSocket) {
    Snake::socket = pSocket;
}

int Snake::getSocket() const {
    return socket;
}
