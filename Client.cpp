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
    //TODO: slovenske vypisy + printf na cout
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
    data.game_over = false;

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

    //vytvorenie vlakna pre zapisovanie dat do socketu <pthread.h>
    std::thread clientThread = std::thread(clientInputHandler, std::ref(data)); // mozno (void*) data
    //v hlavnom vlakne sa bude vykonavat citanie dat zo socketu
    display(data);
    std::cout << "pomocny vypis - pred join" <<std::endl;
    //pockame na skoncenie zapisovacieho vlakna <pthread.h>
    clientThread.join();
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
    //uzavretie socketu <unistd.h>*/
    close(sock);
    return (EXIT_SUCCESS);
}

void clientInputHandler(Data &data) {
    char buffer[BUFFER_LENGTH + 1];
    buffer[BUFFER_LENGTH] = '\0';
    while(!data.game_over) {
        std::cout << "pomocny vypis - zaciatok whilu clientInputHandler" << std::endl;
        bzero(buffer, BUFFER_LENGTH);
//        if (data.game_over) {
//            std::cout << "pomocny vypis - break clientInputHandler" << std::endl;
//            break;
//        }
        fgets(buffer, BUFFER_LENGTH + 1, stdin);
        data.mutex.lock();
        std::cout << "pomocny vypis - zaciatok write clientInputHandler" << std::endl;
        write(data.socket, buffer, strlen(buffer) + 1);
        std::cout << "pomocny vypis - koniec write clientInputHandler" << std::endl;
        data.mutex.unlock();
        std::cout << "pomocny vypis - koniec mutex clientInputHandler" << std::endl;

    }
    std::cout << "pomocny vypis - koniec clientInputHandler" <<std::endl;
}

void display(Data &data) {
    std::string s;
    //ak bude vypis zly, treba upravit velkost buffera
    char buffer[BUFFER_LENGTH + 1];
    buffer[BUFFER_LENGTH] = '\0';
    while(!data.game_over) {
        std::cout << "pomocny vypis - zaciatok whilu display" << std::endl;
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
        usleep(1000);

        bzero(buffer, BUFFER_LENGTH);
        read(data.socket, buffer, BUFFER_LENGTH);
        s = buffer;

        //TODO: spojit v jeden GAMEOVER
        if(!s.empty()) { //s.rfind("Player", 0) == 0
            std::cout << "pomocny vypis - game over display" << std::endl;
            std::cout << s << std::endl;
            std::cout << "Press x to end a game :)" << std::endl;
            data.game_over = true;
        }
    }
    std::cout << "pomocny vypis - koniec display" <<std::endl;

}

