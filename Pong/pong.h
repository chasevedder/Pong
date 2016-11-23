#ifndef PONG_H
#define PONG_H

#include <SDL2/SDL.h>

class Ball;
class Paddle;

class Pong
{
private:
    SDL_Renderer* renderer;
    SDL_Window* window;

    Ball* ball;
    Paddle* player;
    Paddle* enemy;

    int playerScore;
    int enemyScore;

    bool exit;

public:
    Pong();
    ~Pong();

    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;

    void run();
    void handleInput();
    void update();
    void render();
};

#endif // PONG_H
