#include "game.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <enet/enet.h>

#define FRAME_VALUES 100

Uint32 frametimes[FRAME_VALUES];
Uint32 frametimelast;
Uint32 framecount;
float fps;

const int Game::SCREEN_WIDTH = 640;
const int Game::SCREEN_HEIGHT = 480;

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    window = SDL_CreateWindow("PONG by asdfasdf Vedder", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    currentState = NULL;

    memset(frametimes, 0, sizeof(frametimes));
    framecount = 0;
    fps = 0;
    frametimelast = SDL_GetTicks();

    enet_initialize();
    atexit(enet_deinitialize);


}

Game::~Game() {

}

void Game::fpsCalc() {
    Uint32 frametimesindex;
            Uint32 getticks;
            Uint32 count;
            Uint32 i;

            // frametimesindex is the position in the array. It ranges from 0 to FRAME_VALUES.
            // This value rotates back to 0 after it hits FRAME_VALUES.
            frametimesindex = framecount % FRAME_VALUES;

            // store the current time
            getticks = SDL_GetTicks();

            // save the frame time value
            frametimes[frametimesindex] = getticks - frametimelast;

            // save the last frame time for the next fpsthink
            frametimelast = getticks;

            // increment the frame count
            framecount++;

            // Work out the current framerate

            // The code below could be moved into another function if you don't need the value every frame.

            // I've included a test to see if the whole array has been written to or not. This will stop
            // strange values on the first few (FRAME_VALUES) frames.
            if (framecount < FRAME_VALUES) {

                    count = framecount;

            } else {
                    count = FRAME_VALUES;

            }

            // add up all the values and divide to get the average frame time.
            fps = 0;
            for (i = 0; i < count; i++) {

                    fps += frametimes[i];

            }

            fps /= count;

            // now to make it an actual frames per second value...
            fps = 1000.f / fps;
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


    fpsCalc();
    float secondsSinceLastFrame = 1000.0 / fps / 60.0;
    //std::cout << fps << std::endl;


    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    currentState->update(this, &event, renderer, secondsSinceLastFrame);

    //Make sure to exit if update quits
    if (currentState == NULL) return;

    currentState->render(renderer, 0);

    //Update screen
    SDL_RenderPresent(renderer);

    //Max fps 100
    SDL_Delay(10);

}
