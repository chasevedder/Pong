#include "game.h"
#include "pausemenu.h"



int main(int argc, char* argv[]) {
    Game game;
    game.changeState(new PauseMenu());
    while (true) game.update();
    return 0;
}

