#include "paddle.h"
#include "ball.h"
#include "game.h"
#include <iostream>
#include <cmath>

const int Paddle::WIDTH = 10;
const int Paddle::HEIGHT = 50;

Paddle::Paddle(float x, float y) {
    this->x = x;
    this->y = y;
    collided = false;
}

float Paddle::getX() {
    return x;
}

float Paddle::getY() {
    return y;
}

void Paddle::move(float dy) {
    float newY = y + dy;
    if (newY > Game::SCREEN_HEIGHT - HEIGHT)
        newY = Game::SCREEN_HEIGHT - HEIGHT;
    else if (newY < 0)
        newY = 0;
    y = newY;
}

void Paddle::AI(Ball* ball, float deltaTime) {
    if (ball->getX() < Game::SCREEN_WIDTH / 3) return;
    if ((y + WIDTH / 2) < pred) {
        move(14 * deltaTime);
    } else if ((y - WIDTH / 2) > pred) {
        move(-14 * deltaTime);
    }
}

int Paddle::predict(Ball* ball) {
    float slope = ball->getYSpeed() / ball->getXSpeed();
    int prediction = (slope * (x - ball->getX()) + ball->getY());
    prediction = std::abs(prediction);
    int numFlips = prediction / Game::SCREEN_HEIGHT;
    if (numFlips % 2 == 0)
        prediction = prediction % Game::SCREEN_HEIGHT;
    else
        prediction = Game::SCREEN_HEIGHT - (prediction % Game::SCREEN_HEIGHT);
    return prediction - HEIGHT / 2;
}

void Paddle::setPred(int pred) {
    this->pred = pred;
}
