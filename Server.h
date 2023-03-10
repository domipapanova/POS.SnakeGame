#include <cstdio>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>

//#include "Grid.h"
#include "Output.h"
#include "Consts.h"
#include "Game.h"

#ifndef SNAKEGAME_SERVER_H
#define SNAKEGAME_SERVER_H

int server(int argc, char* argv[]);
void play(int clientSocket);

#endif //SNAKEGAME_SERVER_H
