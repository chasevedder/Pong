#include "paddle.h"
#include "pong.h"

const int Paddle::WIDTH = 10;
const int Paddle::HEIGHT = 50;

Paddle::Paddle(int x, int y) {
    this->x = x;
    this->y = y;
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

