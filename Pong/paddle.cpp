#include "paddle.h"
#include "pong.h"
#include "ball.h"
#include <iostream>
#include <cmath>

const int Paddle::WIDTH = 10;
const int Paddle::HEIGHT = 50;

Paddle::Paddle(int x, int y) {
    this->x = x;
    this->y = y;
    collided = false;
}

int Paddle::getX() {
    return x;
}

int Paddle::getY() {
    return y;
}

void Paddle::move(int dy) {
    int newY = y + dy;
    if (newY > Pong::SCREEN_HEIGHT - HEIGHT)
        newY = Pong::SCREEN_HEIGHT - HEIGHT;
    else if (newY < 0)
        newY = 0;
    y = newY;
}

void Paddle::AI(Ball* ball) {
    if (ball->getX() < Pong::SCREEN_WIDTH / 3) return;
    if ((y + WIDTH / 2) < pred) {
        move(2);
    } else if ((y - WIDTH / 2) > pred) {
        move(-2);
    }
}

int Paddle::predict(Ball* ball) {
    float slope = ball->getYSpeed() / ball->getXSpeed();
    int prediction = (slope * (x - ball->getX()) + ball->getY());
    prediction = std::abs(prediction);
    int numFlips = prediction / Pong::SCREEN_HEIGHT;
    if (numFlips % 2 == 0)
        prediction = prediction % Pong::SCREEN_HEIGHT;
    else
        prediction = Pong::SCREEN_HEIGHT - (prediction % Pong::SCREEN_HEIGHT);
    return prediction - HEIGHT / 2;
}

void Paddle::setPred(int pred) {
    this->pred = pred;
}
