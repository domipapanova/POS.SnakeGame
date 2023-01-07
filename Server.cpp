#include "Server.h"

int server(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "You need to initialize the server with the \"port\" argument." << std::endl;
        return (EXIT_FAILURE);
    }
    int port = atoi(argv[1]);
    if (port <= 0) {
        std::cout << "Port has to be a whole number larger than 0." << std::endl;
        return (EXIT_FAILURE);
    }

    // creating TCP socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cout << "Error - socket." << std::endl;
        return (EXIT_FAILURE);
    }

    // definition of the server address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;         // internet sockets
    serverAddress.sin_addr.s_addr = INADDR_ANY; // accepting connections from the internet
    serverAddress.sin_port = htons(port);       // setting up the port

    // binding server address with socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cout << "Error - bind." << std::endl;
        return (EXIT_FAILURE);
    }

    // server listens for new connections through the serverSocket
    std::cout << "Waiting for another player ..." << std::endl;
    listen(serverSocket, 10);

    // server waits for client connection
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);

    // closing passive socket
    close(serverSocket);
    if (clientSocket < 0) {
        std::cout << "Error - accept." << std::endl;
        return (EXIT_FAILURE);

    }

    outputStart(1);
    play(clientSocket);

    outputEnd();
    close(clientSocket);
    return (EXIT_SUCCESS);
}

void play(int clientSocket) {
    srand(time(NULL));
    Game* game = new Game(GAME_WIDTH, GAME_HEIGHT, clientSocket);
    game->start();
    game->stop();
    delete game;
}
