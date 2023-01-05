#include "Server.h"
#include "Game.h"

int server(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "You need to initialize the server with the \"port\" argument." << std::endl;
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
    }

    // definition of the server address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;         // internet sockets
    serverAddress.sin_addr.s_addr = INADDR_ANY; // accepting connections from the internet
    serverAddress.sin_port = htons(port);       // setting up the port

    // binding server address with socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cout << "Error - bind." << std::endl;
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
    }

    std::cout <<"  $$$$$$\\                      $$\\                 \n $$  __$$\\                     $$ |\n $$ /  \\__|$$$$$$$\\   $$$$$$\\  $$ |  $$\\  $$$$$$\\  \n \\$$$$$$\\  $$  __$$\\  \\____$$\\ $$ | $$  |$$  __$$\\ \n  \\____$$\\ $$ |  $$ | $$$$$$$ |$$$$$$  / $$$$$$$$ |\n $$\\   $$ |$$ |  $$ |$$  __$$ |$$  _$$<  $$   ____|\n \\$$$$$$  |$$ |  $$ |\\$$$$$$$ |$$ | \\$$\\ \\$$$$$$$\\ \n  \\______/ \\__|  \\__| \\_______|\\__|  \\__| \\_______|" << std::endl;
    std::cout << "\n\n\n" <<std::endl;
    sleep(2);
    std::cout << "3" << std::endl;
    std::cout << "\n\n\n" <<std::endl;
    sleep(1);
    std::cout << "2" << std::endl;
    std::cout << "\n\n\n" <<std::endl;
    sleep(1);
    std::cout << "1" << std::endl;
    std::cout << "\n\n\n" <<std::endl;
    sleep(1);
    play(clientSocket);
    std::cout << "pomocny vypis - koniec play" << std::endl;

    std::cout << "           /^\\/^\\\n"
             << "         _|__|  O|\n"
             << "\\/     /~     \\_/ \\\n"
             << " \\____|__________/  \\\n"
             << "        \\_______      \\\n"
             << "                `\\     \\                 \\\n"
             << "                  |     |                  \\\n"
             << "                 /      /                    \\\n"
             << "                /     /                       \\\n"
             << "              /      /                         \\ \\\n"
             << "             /     /                            \\  \\\n"
             << "           /     /             _----_            \\   \\\n"
             << "          /     /           _-~      ~-_         |   |\n"
             << "        (      (        _-~    _--_    ~-_     _/   |\n"
             << "        \\      ~-____-~    _-~    ~-_    ~-_-~    /\n"
             << "          ~-_           _-~          ~-_       _-~\n"
             << "            ~--______-~                ~-___-~\n" << std::endl;
    close(clientSocket);
    std::cout << "pomocny vypis - zavretie socketu" << std::endl;
    return (EXIT_SUCCESS);
}

void play(int clientSocket) {
    srand(time(NULL));
    Game* game = new Game(GAME_WIDTH, GAME_HEIGHT, clientSocket);
    game->start();
    std::cout << "pomocny vypis - koniec start" <<std::endl;
    game->stop();
    std::cout << "pomocny vypis - play - pred join" <<std::endl;
    delete game;
    std::cout << "pomocny vypis - game zmazana" <<std::endl;
}
