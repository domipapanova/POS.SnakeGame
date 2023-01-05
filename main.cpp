#include "Server.h"
#include "Client.h"

#include <cstring>
#include <iostream>

    int main (int argc, char* argv[]) {

        //TODO: fixnut ukoncenia hry - vediet sa odpojit
        //TODO: destruktory
        //TODO: MakeFile
        //TODO: kontrola memory leakov
        char* newArgv[argc - 1];
        newArgv[0] = argv[0];

        for(int i = 2; i <= argc - 1; i++) {
            newArgv[i-1] = argv[i];
        }

        if (strcmp(argv[1], "server") == 0) {
            return server(argc - 1, newArgv);
        }
        else if(strcmp(argv[1], "client") == 0) {
            return client(argc - 1, newArgv);
        }
        else {
            fprintf(stderr, "Wrong arguments\n");
            return 1;
        }
    }






