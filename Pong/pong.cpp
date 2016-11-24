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
        player->move(-4);
    }
    else if (keystate[SDL_SCANCODE_S]) {
        player->move(4);
    }
    if (keystate[SDL_SCANCODE_ESCAPE])
        exit = true;
    if (keystate[SDL_SCANCODE_UP])
        enemy->move(-2);
    else if (keystate[SDL_SCANCODE_DOWN])
        enemy->move(2);

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit= true;
        }
    }
}

void Pong::update() {
    ball->move();

    if (ball->getX() < 0 || ball->getX() > SCREEN_WIDTH - (Ball::SIZE)) {
        ball->reset();
        player->collided = false;
        enemy->collided = false;
    }
    if (player->collided == false && ball->collidesWithPaddle(player)) {
        ball->bounce(player);
        player->collided = true;
        enemy->collided = false;
        //Predict a position for the ball
        std::cout << ball->getXSpeed() << ": " << ball->getYSpeed() << std::endl;
        int predY = enemy->predict(ball);
        enemy->setPred(predY);
    }
    else if (enemy->collided == false && ball->collidesWithPaddle(enemy)) {
        ball->bounce(enemy);
        enemy->setPred(SCREEN_HEIGHT / 2);
        enemy->collided = true;
        player->collided = false;
    }
    else if (ball->collidesWithWall()) {
        ball->bounce();
    }
    enemy->AI(ball);
}

void Pong::render() {
    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    //Set color for everything
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //Draw line
    for( int i = 0; i < SCREEN_HEIGHT; i += 4 ) {
        SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, i );
    }

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
