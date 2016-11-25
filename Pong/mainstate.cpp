#include "mainstate.h"

#include "gamestatemanager.h"
#include "pausemenu.h"

MainState::MainState() {

}

MainState::~MainState() {

}

void MainState::onEnter(GameStateManager *gsm, SDL_Renderer* renderer) {

}

void MainState::update(GameStateManager *gsm, SDL_Event* event) {
    while (SDL_PollEvent(event) != 0) {
        if (event->type == SDL_KEYDOWN) {
            if (event->key.keysym.sym == SDLK_ESCAPE) {
                gsm->changeState(new PauseMenu());
            }
        }
    }
}

void MainState::render(SDL_Renderer *renderer) {
    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    //Set color for everything
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //Draw line
    for( int i = 0; i < 480; i += 4 ) {
        SDL_RenderDrawPoint(renderer, 640 / 2, i );
    }



    //Update screen
    SDL_RenderPresent(renderer);
}

void MainState::exit() {

}

