#include "game.h"
#include "SDL2/SDL_ttf.h"

const int Game::SCREEN_WIDTH = 640;
const int Game::SCREEN_HEIGHT = 480;

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    window = SDL_CreateWindow("PONG by asdfasdf Vedder", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    currentState = NULL;
}

Game::~Game() {

}

void Game::changeState(GameState* state) {
    prevState = currentState;
    currentState= state;
    if (currentState != NULL) {
        currentState->exit();

        currentState->onEnter(this, renderer);
    }
}

GameState* Game::getCurrentState() {
    return currentState;
}

GameState* Game::getPrevState() {
    return prevState;
}

void Game::update() {
    //Clear screen

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    currentState->update(this, &event, renderer);

    //Make sure to exit if update quits
    if (currentState == NULL) return;

    currentState->render(renderer, 0);

    SDL_Delay(10);

    //Update screen
    SDL_RenderPresent(renderer);
}
