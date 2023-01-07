#include "Client.h"
#include "Server.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>

int client(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << ("You need to initialize the client with the \"address\" and \"port\" arguments.") << std::endl;
        return (EXIT_FAILURE);
    }

    // getting server address and port
    struct hostent *server = gethostbyname(argv[1]);
    if (server == NULL) {
        std::cout << ("Server does not exist.") << std::endl;
        return (EXIT_FAILURE);
    }
    int port = atoi(argv[2]);
    if (port <= 0) {
        std::cout << "Port has to be a whole number larger than 0." << std::endl;
        return (EXIT_FAILURE);
    }

    // creating socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cout << "Error - socket." << std::endl;
        return (EXIT_FAILURE);
    }

    // definition of the server address
    struct sockaddr_in serverAddress;
    bzero((char *)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);
    serverAddress.sin_port = htons(port);

    if (connect(sock,(struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cout << "Error - connect." << std::endl;
        return (EXIT_FAILURE);
    }

    // initialization of data to be sent between threads
    Data data;
    data.socket = sock;
    data.game_over = false;

    outputStart(2);

    // creating thread for writing data to socket
    std::thread clientThread = std::thread(clientInputHandler, std::ref(data));

    // reading data from socket
    display(data);

    // waiting for the writing thread to end
    clientThread.join();

    outputEnd();

    // closing the socket
    close(sock);
    return (EXIT_SUCCESS);
}



void clientInputHandler(Data &data) {
    char buffer[BUFFER_LENGTH + 1];
    buffer[BUFFER_LENGTH] = '\0';
    while(!data.game_over) {
        bzero(buffer, BUFFER_LENGTH);
        fgets(buffer, BUFFER_LENGTH + 1, stdin);
        data.mutex.lock();
        write(data.socket, buffer, strlen(buffer) + 1);
        data.mutex.unlock();
    }
}

void display(Data &data) {
    std::string s;
    char buffer[BUFFER_LENGTH + 1];
    buffer[BUFFER_LENGTH] = '\0';
    while(!data.game_over) {
        bzero(buffer, BUFFER_LENGTH);
        read(data.socket, buffer, BUFFER_LENGTH);
        s = buffer;
        for (int y = 0; y < GAME_HEIGHT; y++) {
            std::cout << BLUE_LINE;
            for (int x = 0; x < GAME_WIDTH; x++) {
                char out = s[y * GAME_WIDTH + x];
                switch (out) {
                    case ' ':
                        std::cout << " ";
                        break;
                    case 'o':
                        std::cout << GREEN_o;
                        break;
                    case 's':
                        std::cout << YELLOW_o;
                        break;
                    case 'x':
                        std::cout << RED_x;
                        break;
                    case 'O':
                        std::cout << GREEN_O;
                        break;
                    case 'S':
                        std::cout << YELLOW_O;
                        break;
                }
            }
            std::cout << BLUE_LINE;
            std::cout << std::endl;
        }
        std::cout << "\n\n\n";
        usleep(1000);

        bzero(buffer, BUFFER_LENGTH);
        read(data.socket, buffer, BUFFER_LENGTH);
        s = buffer;

        if(!s.empty()) {
            std::cout << s << std::endl;
            std::cout << "Press x to end the game :)" << std::endl;
            data.game_over = true;
        }
    }
}