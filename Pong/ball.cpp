#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

#include "ball.h"
#include "paddle.h"
#include "game.h"
#include <cmath>
#include <iostream>
#include <random>

const int Ball::SIZE = 10;


Ball::Ball(int x, int y) {
    this->x = x;
    this->y = y;
    this->xSpeed = -14;
    this->ySpeed = 14;
    this->numHits = 0;
    started = false;
}

float Ball::getX() {
    return x;
}

float Ball::getY() {
    return y;
}

bool Ball::collidesWithPaddle(Paddle* paddle) {
    //Check collision with left paddle
    if (paddle->getX() < Game::SCREEN_WIDTH / 2) {
        if (x <= paddle->getX() + Paddle::WIDTH && y >= paddle->getY() && y <= paddle->getY() + Paddle::HEIGHT && x + SIZE >= paddle->getX()) {

            return true;
        }
    }
    //Check collision with right paddle
    else {
        if (x >= paddle->getX() && y + SIZE >= paddle->getY() && y <= paddle->getY() + Paddle::HEIGHT && x <= paddle->getX() + Paddle::WIDTH) {

            return true;
        }
    }
    return false;

}

bool Ball::collidesWithWall() {
    //Check ceiling
    if (y <= 0)
        return true;
    else if (y >= Game::SCREEN_HEIGHT - SIZE)
        return true;
    return false;
}

void Ball::move(float deltaTime) {

    prevX = x;
    prevY = y;
    x += xSpeed * deltaTime;
    y += ySpeed * deltaTime;
}

float Ball::slope() {
    return (y-prevY) / (x-prevX);
}

void Ball::bounce(Paddle* paddle) {
    numHits++;
    if (numHits > 5) {
        if (xSpeed < 0)
            xSpeed -= 2;
        else
            xSpeed += 2;
        if (ySpeed < 0)
            ySpeed -= 2;
        else
            ySpeed += 2;
        numHits = 0;
    }
    if (paddle != NULL){
        xSpeed *= -1;
    }

    float magnitude = std::sqrt(ySpeed*ySpeed + xSpeed * xSpeed);
    int sign = (paddle->getX() < Game::SCREEN_WIDTH/2) ? 1 : -1;

    int relative_y = (y - paddle->getY() + SIZE);

    float  angle = (2.14f * relative_y - 75.0f);

       // Convert angle to radian, find its cos() and multiply by the speed.
    xSpeed = sign*magnitude*std::cos(angle*M_PI/180.0f);

       // Convert angle to radina, find its sin() and multiply by the speed.
    ySpeed = magnitude*std::sin(angle*M_PI/180.0f);

    /*
    int distanceFromCenter = y + (SIZE / 2) - (paddle->getY() + (Paddle::HEIGHT / 2));
    float exitAngle = std::atan(-ySpeed / -xSpeed);
    exitAngle = exitAngle * 180.0 / M_PI;
    if (distanceFromCenter < -15) {
        if (ySpeed < 0) {
            exitAngle *= 1.2;
        } else {
            exitAngle /= 1.2;
        }
    }
    else if (distanceFromCenter > 15) {
        if (ySpeed < 0) {
            exitAngle /= 1.2;
        } else {
            exitAngle *= 1.2;
        }
    }

    float newY = magnitude * std::sin(exitAngle * M_PI / 180.0);
    float newX = magnitude * std::cos(exitAngle * M_PI / 180.0);
    if (xSpeed < 0) {
        newX *= -1;
        newY *= -1;
    }
    ySpeed = newY;
    xSpeed = newX;
    speed *= 1;
    */
}

void Ball::bounce() {
    ySpeed *= -1;
}

void Ball::reset() {
    started = true;
    x = (Game::SCREEN_WIDTH / 2) - (SIZE / 2);
    y = (Game::SCREEN_HEIGHT / 2) - (SIZE / 2);

    xSpeed = (std::rand() % 2) == 0 ? 14: -14;
    ySpeed = (std::rand() % 2) == 0 ? 14: -14;
}

float Ball::getXSpeed() {
    return xSpeed;
}

float Ball::getYSpeed() {
    return ySpeed;
}



