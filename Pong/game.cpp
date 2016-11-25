#include "game.h"
#include "SDL2/SDL_ttf.h"

const int Game::SCREEN_WIDTH = 640;
const int Game::SCREEN_HEIGHT = 480;

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    window = SDL_CreateWindow("PONG by asdfasdf Vedder", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Game::~Game() {

}

void Game::changeState(GameState* state) {
    currentState= state;
    currentState->onEnter(this, renderer);
}

GameState* Game::getCurrentState() {
    return currentState;
}

void Game::update() {
    currentState->update(this, &event);
    currentState->render(renderer);

    //Handle exit regardless of state
    if (event.type == SDL_QUIT)
        currentState = NULL;
}
