#include "Server.h"
#include "Game.h"


int server(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Sever je nutne spustit s nasledujucimi argumentmi: port .");
    }
    int port = atoi(argv[1]);
    if (port <= 0) {
        printf("Port musi byt cele cislo vacsie ako 0.");
    }

    //vytvorenie TCP socketu <sys/socket.h>
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        printf("Chyba - socket.");
    }

    //definovanie adresy servera <arpa/inet.h>
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;         //internetove sockety
    serverAddress.sin_addr.s_addr = INADDR_ANY; //prijimame spojenia z celeho internetu
    serverAddress.sin_port = htons(port);       //nastavenie portu

    //prepojenie adresy servera so socketom <sys/socket.h>
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        printf("Chyba - bind.");
    }

    //server bude prijimat nove spojenia cez socket serverSocket <sys/socket.h>
    printf("Waiting for another player");
    listen(serverSocket, 10);

    //server caka na pripojenie klienta <sys/socket.h>
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);

    //uzavretie pasivneho socketu <unistd.h>
    close(serverSocket);
    if (clientSocket < 0) {
        printf("Chyba - accept.");
    }

    play(clientSocket);
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
