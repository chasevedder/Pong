#include "ball.h"
#include "paddle.h"
#include "pong.h";
#include <cmath>

const int Ball::SIZE = 10;

Ball::Ball(int x, int y) {
    this->x = x;
    this->y = y;
    this->speed = 4;
    this->angle = 180;
}

int Ball::getX() {
    return x;
}

int Ball::getY() {
    return y;
}

bool Ball::collidesWithPaddle(Paddle* paddle) {
    //Check collision with left paddle
    if (paddle->getX() < Pong::SCREEN_WIDTH / 2) {
        if (x <= paddle->getX() + Paddle::WIDTH && y > paddle->getY() && y < paddle->getY() + Paddle::HEIGHT)
            return true;
    }
    //Check collision with right paddle
    else {
        if (x >= paddle->getX() && y > paddle->getY() && y < paddle->getY() + Paddle::HEIGHT)
            return true;
    }
    return false;

}

void Ball::move() {
    x += speed * std::cos(angle * M_PI / 180.0f);
    y += speed * std::sin(angle * M_PI / 180.0f);
}

void Ball::bounce() {
    speed *= -1;
}



