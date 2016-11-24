#include "ball.h"
#include "paddle.h"
#include "pong.h";
#include <cmath>
#include <iostream>

const int Ball::SIZE = 10;


Ball::Ball(int x, int y) {
    this->x = x;
    this->y = y;
    this->xSpeed = -2;
    this->ySpeed = 2;
    this->numHits = 0;
}

float Ball::getX() {
    return x;
}

float Ball::getY() {
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
        if (x >= paddle->getX() && y + SIZE > paddle->getY() && y < paddle->getY() + Paddle::HEIGHT) {

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
    //numHits++;
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
    int distanceFromCenter = y + (SIZE / 2) - (paddle->getY() + (Paddle::HEIGHT / 2));
    float exitAngle = std::atan(-ySpeed / -xSpeed);
    exitAngle = exitAngle * 180.0 / M_PI;
    if (distanceFromCenter < -10) {
        if (ySpeed < 0) {
            exitAngle *= 1.2;
        } else {
            exitAngle /= 1.2;
        }
    }
    else if (distanceFromCenter > 10) {
        if (ySpeed < 0) {
            exitAngle /= 1.2;
        } else {
            exitAngle *= 1.2;
        }
    }
    float magnitude = std::sqrt(ySpeed*ySpeed + xSpeed * xSpeed);
    float newY = magnitude * std::sin(exitAngle * M_PI / 180.0);
    float newX = magnitude * std::cos(exitAngle * M_PI / 180.0);
    if (xSpeed < 0) {
        newX *= -1;
        newY *= -1;
    }
    ySpeed = newY;
    xSpeed = newX;
    speed *= 1;
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

float Ball::getXSpeed() {
    return xSpeed;
}

float Ball::getYSpeed() {
    return ySpeed;
}


