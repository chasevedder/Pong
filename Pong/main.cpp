#include "game.h"
#include "mainstate.h"

#include <iostream>

int main(int argc, char* argv[]) {
    Game game;
    game.changeState(new MainState());
    while (game.getCurrentState() != NULL) game.update();
    std::cout << "done" << std::endl;

    return 0;
}

