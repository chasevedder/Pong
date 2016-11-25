#include "pausemenu.h"
#include "gamestatemanager.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>

#include "mainstate.h"

PauseMenu::PauseMenu() {


}

PauseMenu::~PauseMenu() {
    TTF_CloseFont(font);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(message);
}

void PauseMenu::onEnter(GameStateManager* gsm, SDL_Renderer* renderer) {
    font = TTF_OpenFont("../resources/OpenSans-Regular.ttf", 24);
    white = {255, 255, 255};
    surf = TTF_RenderText_Solid(font, "PAUSED", white);

    message = SDL_CreateTextureFromSurface(renderer, surf);
    messageRect = {50, 50, 200, 200 };
}

void PauseMenu::update(GameStateManager* gsm, SDL_Event* event) {
    while (SDL_PollEvent(event) != 0) {
        std::cout << "event" << std::endl;
        if (event->type = SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
            if (event->button.x > messageRect.x &&
                    event->button.x < messageRect.x + messageRect.w &&
                    event->button.y > messageRect.y &&
                    event->button.y < messageRect.y + messageRect.h) {
                std::cout << "Unpause" << std::endl;
                exit();
                gsm->changeState(new MainState());
            }
        }
    }
}

void PauseMenu::render(SDL_Renderer *renderer) {
    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, message, NULL, &messageRect);



    //Update screen
    SDL_RenderPresent(renderer);
}

void PauseMenu::exit() {

}
