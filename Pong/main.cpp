#include "game.h"
#include "mainmenu.h"

#include <iostream>

int main(int argc, char* argv[]) {
    Game game;
    game.changeState(new MainMenu());
    while (game.getCurrentState() != NULL) game.update();
    std::cout << "done" << std::endl;

    return 0;
}

