#ifndef SNAKEGAME_CLIENT_H
#define SNAKEGAME_CLIENT_H

#include <mutex>

#include "Output.h"
#include "Consts.h"

struct Data {
    std::mutex mutex;
    int socket;
//    std::vector<std::vector<Cell>> cells;
    bool game_over;
};

int client(int argc, char *argv[]);
static void clientInputHandler(Data& data);
static void display(Data& data);

#endif //SNAKEGAME_CLIENT_H