#include "pausemenu.h"
#include "game.h"
#include "gamestatemanager.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>

#include "mainstate.h"

enum Colors {
    WHITE,
    RED,
    BLUE
};

PauseMenu::PauseMenu() {

}

PauseMenu::~PauseMenu() {

    SDL_DestroyTexture(title);
}

void PauseMenu::onEnter(GameStateManager* gsm, SDL_Renderer* renderer) {
    //Initialize fonts and colors
    titleFont = TTF_OpenFont("../resources/OpenSans-Regular.ttf", 56);
    optionsFont = TTF_OpenFont("../resources/OpenSans-Regular.ttf", 36);
    colors[0] = {255, 255, 255};
    colors[1] = {255, 0, 0};
    colors[2] = {0, 0, 255};

    SDL_Surface* surf = TTF_RenderText_Solid(titleFont, "PAUSED", colors[Colors::BLUE]);

    TTF_SizeText(titleFont, "PAUSED", &titleRect.w, &titleRect.h);
    title = SDL_CreateTextureFromSurface(renderer, surf);
    titleRect.x = (Game::SCREEN_WIDTH / 2) - (surf->w / 2);
    titleRect.y = 50;

    //Initialize options
    optionsText[0] = "Resume";
    surf = TTF_RenderText_Solid(optionsFont, optionsText[0], colors[Colors::WHITE]);
    TTF_SizeText(optionsFont, optionsText[0], &pos[0].w, &pos[0].h);
    options[0] = SDL_CreateTextureFromSurface(renderer, surf);
    pos[0].x = (Game::SCREEN_WIDTH / 2) - (surf->w / 2);
    pos[0].y = 150;
    selected[0] = false;

    optionsText[1] = "Quit";
    surf = TTF_RenderText_Solid(optionsFont, optionsText[1], colors[Colors::WHITE]);
    TTF_SizeText(optionsFont, optionsText[1], &pos[1].w, &pos[1].h);
    options[1] = SDL_CreateTextureFromSurface(renderer, surf);
    pos[1].x = (Game::SCREEN_WIDTH / 2) - (surf->w / 2);
    pos[1].y = 200;
    selected[0] = false;


    SDL_FreeSurface(surf);
}

void PauseMenu::update(GameStateManager* gsm, SDL_Event* event, SDL_Renderer* renderer) {
    while (SDL_PollEvent(event) != 0) {
        if (event->type == SDL_QUIT) {
            gsm->changeState(NULL);
        }
        else if (event->type == SDL_KEYDOWN) {
            if (event->key.keysym.sym == SDLK_ESCAPE) {
                gsm->changeState(gsm->getPrevState());
            }
        }
        else if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
            for (int i = 0; i < NUM_OPTS; i++) {
                if (event->button.x > pos[i].x &&
                        event->button.x < pos[i].x + pos[i].w &&
                        event->button.y > pos[i].y &&
                        event->button.y < pos[i].y + pos[i].h) {
                    if (i == 0) //Resume
                        gsm->changeState(gsm->getPrevState());
                    else if (i == 1) // Quit
                        gsm->changeState(NULL);
                }
            }
        }
        else if (event->type == SDL_MOUSEMOTION) {
            for (int i = 0; i < NUM_OPTS; i++) {
                if (event->button.x > pos[i].x &&
                        event->button.x < pos[i].x + pos[i].w &&
                        event->button.y > pos[i].y &&
                        event->button.y < pos[i].y + pos[i].h) {
                    if (!selected[i]) {
                        selected[i] = true;
                        SDL_Color red = {255, 0, 0};
                        SDL_Surface* surf = TTF_RenderText_Solid(optionsFont, optionsText[i], colors[Colors::RED]);
                        options[i] = SDL_CreateTextureFromSurface(renderer, surf);
                    }
                }
                else {
                    if (selected[i]) {
                        selected[i] = false;
                        SDL_Color white = {255, 255, 255};
                        SDL_Surface* surf = TTF_RenderText_Solid(optionsFont, optionsText[i], colors[Colors::WHITE]);
                        options[i] = SDL_CreateTextureFromSurface(renderer, surf);
                    }
                }
            }
        }
    }
    if (gsm->getPrevState() != NULL) {
        gsm->getPrevState()->render(renderer, 0xCC);
    }
}

void PauseMenu::render(SDL_Renderer *renderer, Uint8 alpha) {



    SDL_RenderCopy(renderer, title, NULL, &titleRect);

    //Render options
    for (int i = 0; i < NUM_OPTS; i++) {
        SDL_RenderCopy(renderer, options[i], NULL, &pos[i]);
    }



}

void PauseMenu::exit() {

}
