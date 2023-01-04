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
    if (argc < 2) {
        printf("Klienta je nutne spustit s nasledujucimi argumentmi: adresa port pouzivatel.");
    }

    //ziskanie adresy a portu servera <netdb.h>
    struct hostent *server = gethostbyname(argv[1]);
    if (server == NULL) {
        printf("Server neexistuje.");
    }
    int port = atoi(argv[2]);
    if (port <= 0) {
        printf("Port musi byt cele cislo vacsie ako 0.");
    }
    char *userName = argv[3];

    //vytvorenie socketu <sys/socket.h>
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Chyba - socket.");
    }

    //definovanie adresy servera <arpa/inet.h>
    struct sockaddr_in serverAddress;
    bzero((char *)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);
    serverAddress.sin_port = htons(port);

    if (connect(sock,(struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        printf("Chyba - connect.");
    }

    //inicializacia dat zdielanych medzi vlaknami
    Data data;
    data.socket = sock;

    //vytvorenie vlakna pre zapisovanie dat do socketu <pthread.h>

    std::thread clientThread = std::thread(clientInputHandler, std::ref(data)); // mozno (void*) data
    //v hlavnom vlakne sa bude vykonavat citanie dat zo socketu
    display(data);

    //pockame na skoncenie zapisovacieho vlakna <pthread.h>
    clientThread.join();

    //uzavretie socketu <unistd.h>*/
    close(sock);

    return (EXIT_SUCCESS);
}

void clientInputHandler(Data &data) {
    char buffer[BUFFER_LENGTH + 1];
    buffer[BUFFER_LENGTH] = '\0';
    while(true) {
        bzero(buffer, BUFFER_LENGTH);
        fgets(buffer, BUFFER_LENGTH + 1, stdin);
        data.mutex.lock();
        write(data.socket, buffer, strlen(buffer) + 1);
        data.mutex.unlock();
    }
}

void display(Data &data) {
    std::string s;
    //ak bude vypis zly, treba upravit velkost buffera
    char buffer[BUFFER_LENGTH + 1];
    buffer[BUFFER_LENGTH] = '\0';
    while(true) {
        bzero(buffer, BUFFER_LENGTH);
        read(data.socket, buffer, BUFFER_LENGTH);
        s = buffer;


        for (int y = 0; y < GAME_HEIGHT; y++) {
            std::cout << "|";
            for (int x = 0; x < GAME_WIDTH; x++) {
                std::cout << s[y * GAME_WIDTH + x];
            }
            std::cout << "|";
            std::cout << std::endl;
        }
        std::cout << "\n\n\n";


    }
}

