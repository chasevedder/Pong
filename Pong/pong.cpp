#include "pong.h"

const int Pong::SCREEN_WIDTH = 640;
const int Pong::SCREEN_HEIGHT = 480;

#include "paddle.h"
#include "ball.h"
#include <iostream>

Pong::Pong() {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("PONG by Chase Vedder", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    player = new Paddle(20, (SCREEN_HEIGHT / 2) - (Paddle::HEIGHT / 2));
    enemy = new Paddle(SCREEN_WIDTH - Paddle::WIDTH - 20, SCREEN_HEIGHT / 2 - Paddle::HEIGHT / 2);

    ball = new Ball((SCREEN_WIDTH / 2) - (Ball::SIZE / 2), (SCREEN_HEIGHT / 2) - (Ball::SIZE / 2));

    exit = false;
}

Pong::~Pong() {

}

void Pong::run() {
    while (!exit) {
        handleInput();
        update();
        render();
        SDL_Delay(10);
    }
}

void Pong::handleInput() {

//    /SDL_PumpEvents();
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_W]) {
        player->move(-2);
    }
    else if (keystate[SDL_SCANCODE_S]) {
        player->move(2);
    }
    if (keystate[SDL_SCANCODE_ESCAPE])
        exit = true;

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit= true;
        }
    }
}

void Pong::update() {
    ball->move();
    if (ball->collidesWithPaddle(player) || ball->collidesWithPaddle(enemy)) {
        ball->bounce();
    }
}

void Pong::render() {
    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    //Set color for everything
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //Draw player
    SDL_Rect playerRect = {player->getX(), player->getY(), Paddle::WIDTH, Paddle::HEIGHT};
    SDL_RenderFillRect(renderer, &playerRect);

    //Draw enemy
    SDL_Rect enemyRect = {enemy->getX(), enemy->getY(), Paddle::WIDTH, Paddle::HEIGHT};
    SDL_RenderFillRect(renderer, &enemyRect);

    //Draw ball
    SDL_Rect ballRect = {ball->getX(), ball->getY(), Ball::SIZE, Ball::SIZE};
    SDL_RenderFillRect(renderer, &ballRect);


    //Update screen
    SDL_RenderPresent(renderer);
}
