

#ifndef SNAKEGAME_CLIENT_H
#define SNAKEGAME_CLIENT_H

#include <mutex>
#include <vector>

#include "Grid.h"
#include "Game.h"

struct Data {
    std::mutex mutex;
    int socket;
    std::vector<std::vector<Cell>> cells;
};

int client(int argc, char *argv[]);
static void clientInputHandler(Data& data);
static void display(Data& data);

#endif //SNAKEGAME_CLIENT_H
