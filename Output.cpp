#include "Output.h"

void outputStart() {
    std::cout << "  $$$$$$\\                      $$\\                 \n" <<
              " $$  __$$\\                     $$ |\n" <<
              " $$ /  \\__|$$$$$$$\\   $$$$$$\\  $$ |  $$\\  $$$$$$\\  \n" <<
              " \\$$$$$$\\  $$  __$$\\  \\____$$\\ $$ | $$  |$$  __$$\\ \n" <<
              "  \\____$$\\ $$ |  $$ | $$$$$$$ |$$$$$$  / $$$$$$$$ |\n" <<
              " $$\\   $$ |$$ |  $$ |$$  __$$ |$$  _$$<  $$   ____|\n" <<
              " \\$$$$$$  |$$ |  $$ |\\$$$$$$$ |$$ | \\$$\\ \\$$$$$$$\\ \n" <<
              "  \\______/ \\__|  \\__| \\_______|\\__|  \\__| \\_______|" << std::endl;

    std::cout << "\n\n" <<std::endl;
    std::cout << "Control your snake with WASD\nPress X to terminate the game.\n\nFirst to reach 20 cells wins!" << std::endl;
    sleep(3);
    std::cout << "\n\n" <<std::endl;
    std::cout << "    ____                 __     \n" <<
              "   / __ \\___  ____ _____/ /_  __\n" <<
              "  / /_/ / _ \\/ __ `/ __  / / / /\n" <<
              " / _, _/  __/ /_/ / /_/ / /_/ / \n" <<
              "/_/ |_|\\___/\\__,_/\\__,_/\\__, /  \n" <<
              "                       /____/   " << std::endl;
    std::cout << "\n\n\n" <<std::endl;
    sleep(1);
    std::cout << "   _____      __ \n" <<
              "  / ___/___  / /_\n" <<
              "  \\__ \\/ _ \\/ __/\n" <<
              " ___/ /  __/ /_  \n" <<
              "/____/\\___/\\__/ " << std::endl;
    std::cout << "\n\n\n" <<std::endl;
    sleep(1);
    std::cout << "   __________  __\n" <<
              "  / ____/ __ \\/ /\n" <<
              " / / __/ / / / / \n" <<
              "/ /_/ / /_/ /_/  \n" <<
              "\\____/\\____(_) " << std::endl;
    std::cout << "\n" <<std::endl;
    sleep(1);
}

void outputEnd() {
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
}