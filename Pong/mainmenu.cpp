#include "mainmenu.h"
#include "game.h"
#include "mainstate.h"
#include "multiplayerstate.h"

enum Colors {
    WHITE,
    RED,
    BLUE
};

MainMenu::MainMenu() {

}

MainMenu::~MainMenu() {

}

void MainMenu::onEnter(GameStateManager *gsm, SDL_Renderer *renderer) {
    //Initialize fonts and colors
    titleFont = TTF_OpenFont("../resources/OpenSans-Regular.ttf", 72);
    optionsFont = TTF_OpenFont("../resources/OpenSans-Regular.ttf", 36);
    colors[0] = {255, 255, 255};
    colors[1] = {255, 0, 0};
    colors[2] = {0, 0, 255};

    SDL_Surface* surf = TTF_RenderText_Solid(titleFont, "PONG", colors[WHITE]);

    TTF_SizeText(titleFont, "PONG", &titleRect.w, &titleRect.h);
    title = SDL_CreateTextureFromSurface(renderer, surf);
    titleRect.x = (Game::SCREEN_WIDTH / 2) - (surf->w / 2);
    titleRect.y = 50;

    //Initialize options
    optionsText[0] = "Play";
    surf = TTF_RenderText_Solid(optionsFont, optionsText[0], colors[WHITE]);
    TTF_SizeText(optionsFont, optionsText[0], &pos[0].w, &pos[0].h);
    options[0] = SDL_CreateTextureFromSurface(renderer, surf);
    pos[0].x = (Game::SCREEN_WIDTH / 2) - (surf->w / 2);
    pos[0].y = 150;
    selected[0] = false;
    visible[0] = true;

    optionsText[1] = "Multiplayer";
    surf = TTF_RenderText_Solid(optionsFont, optionsText[1], colors[WHITE]);
    TTF_SizeText(optionsFont, optionsText[1], &pos[1].w, &pos[1].h);
    options[1] = SDL_CreateTextureFromSurface(renderer, surf);
    pos[1].x = (Game::SCREEN_WIDTH / 2) - (surf->w / 2);
    pos[1].y = 200;
    selected[1] = false;
    visible[1] = true;

    optionsText[2] = "Quit";
    surf = TTF_RenderText_Solid(optionsFont, optionsText[2], colors[WHITE]);
    TTF_SizeText(optionsFont, optionsText[2], &pos[2].w, &pos[2].h);
    options[2] = SDL_CreateTextureFromSurface(renderer, surf);
    pos[2].x = (Game::SCREEN_WIDTH / 2) - (surf->w / 2);
    pos[2].y = 250;
    selected[2] = false;
    visible[2] = true;


    SDL_FreeSurface(surf);
}

void MainMenu::update(GameStateManager *gsm, SDL_Event *event, SDL_Renderer *renderer, float deltaTime) {
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
                if (visible[i] &&
                        event->button.x > pos[i].x &&
                        event->button.x < pos[i].x + pos[i].w &&
                        event->button.y > pos[i].y &&
                        event->button.y < pos[i].y + pos[i].h) {
                    if (i == 0) //Resume
                        gsm->changeState(new MultiplayerState());
                    else if (i == 1) {//Options
                        //Open options menu
                    }
                    else if (i == 2) // Quit
                        gsm->changeState(NULL);
                }
            }
        }
        else if (event->type == SDL_MOUSEMOTION) {
            for (int i = 0; i < NUM_OPTS; i++) {
                if (visible[i] &&
                        event->button.x > pos[i].x &&
                        event->button.x < pos[i].x + pos[i].w &&
                        event->button.y > pos[i].y &&
                        event->button.y < pos[i].y + pos[i].h) {
                    if (!selected[i]) {
                        selected[i] = true;
                        SDL_Surface* surf = TTF_RenderText_Solid(optionsFont, optionsText[i], colors[RED]);
                        options[i] = SDL_CreateTextureFromSurface(renderer, surf);
                    }
                }
                else {
                    if (selected[i]) {
                        selected[i] = false;
                        SDL_Surface* surf = TTF_RenderText_Solid(optionsFont, optionsText[i], colors[WHITE]);
                        options[i] = SDL_CreateTextureFromSurface(renderer, surf);
                    }
                }
            }
        }
    }

}

void MainMenu::render(SDL_Renderer *renderer, Uint8 alpha) {
    SDL_RenderCopy(renderer, title, NULL, &titleRect);
    for (int i = 0; i < NUM_OPTS; i++) {
        if (visible[i])
            SDL_RenderCopy(renderer, options[i], NULL, &pos[i]);
    }
}

void MainMenu::exit() {

}

