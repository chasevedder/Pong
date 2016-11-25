#include "game.h"
#include "mainstate.h"



int main(int argc, char* argv[]) {
    Game game;
    game.changeState(new MainState());
    while (game.getCurrentState() != NULL) game.update();
    return 0;
}

