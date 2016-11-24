#include "pausemenu.h"
#include "gamestatemanager.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

PauseMenu::PauseMenu() {
    font = TTF_OpenFont("../resources/OpenSans-Regular.ttf", 24);
    white = {255, 255, 255};
    surf = TTF_RenderText_Solid(font, "PAUSED", white);

    messageRect = {50, 50, 200, 200 };
}

PauseMenu::~PauseMenu() {

}

void PauseMenu::onEnter(GameStateManager* gsm) {

}

void PauseMenu::update(GameStateManager* gsm) {

}

void PauseMenu::render(SDL_Renderer *renderer) {
    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    if (message == NULL)
    message = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_RenderCopy(renderer, message, NULL, &messageRect);



    //Update screen
    SDL_RenderPresent(renderer);
}

void PauseMenu::exit() {

}
