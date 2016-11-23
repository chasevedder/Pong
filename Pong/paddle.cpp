#include "paddle.h"

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

