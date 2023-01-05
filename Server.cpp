#include "Server.h"
#include "Game.h"


int server(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "You need to initialize the server with the \"port\" argument." << std::endl;
    }
    int port = atoi(argv[1]);
    if (port <= 0) {
        std::cout <<"Port needs to be a whole number larger than 0." << std::endl;
    }

    //vytvorenie TCP socketu <sys/socket.h>
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cout << "Error - socket." << std::endl;
    }

    //definovanie adresy servera <arpa/inet.h>
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;         //internetove sockety
    serverAddress.sin_addr.s_addr = INADDR_ANY; //prijimame spojenia z celeho internetu
    serverAddress.sin_port = htons(port);       //nastavenie portu

    //prepojenie adresy servera so socketom <sys/socket.h>
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cout << "Error - bind." << std::endl;
    }

    //server bude prijimat nove spojenia cez socket serverSocket <sys/socket.h>
    std::cout << "Waiting for another player ..." << std::endl;
    listen(serverSocket, 10);

    //server caka na pripojenie klienta <sys/socket.h>
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);

    //uzavretie pasivneho socketu <unistd.h>
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

    std::cout<<"           /^\\/^\\\n"
             <<"         _|__|  O|\n"
             <<"\\/     /~     \\_/ \\\n"
             <<" \\____|__________/  \\\n"
             <<"        \\_______      \\\n"
             <<"                `\\     \\                 \\\n"
             <<"                  |     |                  \\\n"
             <<"                 /      /                    \\\n"
             <<"                /     /                       \\\n"
             <<"              /      /                         \\ \\\n"
             <<"             /     /                            \\  \\\n"
             <<"           /     /             _----_            \\   \\\n"
             <<"          /     /           _-~      ~-_         |   |\n"
             <<"        (      (        _-~    _--_    ~-_     _/   |\n"
             <<"        \\      ~-____-~    _-~    ~-_    ~-_-~    /\n"
             <<"          ~-_           _-~          ~-_       _-~\n"
             <<"            ~--______-~                ~-___-~\n"<<std::endl;
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
