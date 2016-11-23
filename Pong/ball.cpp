#include "ball.h"
#include "paddle.h"
#include "pong.h";
#include <cmath>

const int Ball::SIZE = 10;

Ball::Ball(int x, int y) {
    this->x = x;
    this->y = y;
    this->xSpeed = -2;
    this->ySpeed = 2;
    this->numHits = 0;
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
        if (x <= paddle->getX() + Paddle::WIDTH && y > paddle->getY() && y < paddle->getY() + Paddle::HEIGHT) {

            return true;
        }
    }
    //Check collision with right paddle
    else {
        if (x >= paddle->getX() && y > paddle->getY() && y < paddle->getY() + Paddle::HEIGHT) {

            return true;
        }
    }
    return false;

}

bool Ball::collidesWithWall() {
    //Check ceiling
    if (y <= 0)
        return true;
    else if (y >= Pong::SCREEN_HEIGHT - SIZE)
        return true;
    return false;
}

void Ball::move() {

    prevX = x;
    prevY = y;
    x += xSpeed;
    y += ySpeed;
}

float Ball::slope() {
    return (y-prevY) / (x-prevX);
}

void Ball::bounce(Paddle* paddle) {
    numHits++;
    if (numHits > 5) {
        if (xSpeed < 0)
            xSpeed--;
        else
            xSpeed++;
        if (ySpeed < 0)
            ySpeed--;
        else
            ySpeed++;
        numHits = 0;
    }
    if (paddle != NULL){
        xSpeed *= -1;
    }

    speed *= -1;
}

void Ball::bounce() {
    ySpeed *= -1;
}

void Ball::reset() {
    x = (Pong::SCREEN_WIDTH / 2) - (SIZE / 2);
    y = (Pong::SCREEN_HEIGHT / 2) - (SIZE / 2);
    xSpeed = -2;
    ySpeed = 2;
}

int Ball::getXSpeed() {
    return xSpeed;
}

int Ball::getYSpeed() {
    return ySpeed;
}
