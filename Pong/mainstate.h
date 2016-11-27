#ifndef MAINSTATE_H
#define MAINSTATE_H

#include "gamestate.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "ball.h"
#include "paddle.h"
#include <string>

class GameStateManager;

class MainState : public GameState
{
private:

    Ball* ball;
    Paddle* player;
    Paddle* enemy;

    int playerScore;
    int enemyScore;

    TTF_Font* font;
    SDL_Texture* playerScoreText;
    SDL_Texture* enemyScoreText;
    SDL_Texture* startText;
    SDL_Texture* winText;
    SDL_Rect playerScoreRect;
    SDL_Rect enemyScoreRect;
    SDL_Rect startRect;
    SDL_Rect winRect;
    SDL_Color white;
public:
    MainState();
    virtual ~MainState();
    virtual void onEnter(GameStateManager* gsm, SDL_Renderer* renderer);
    virtual void update(GameStateManager* gsm, SDL_Event* event, SDL_Renderer* renderer, float deltaTime);
    virtual void render(SDL_Renderer* renderer, Uint8 alpha);
    virtual void exit();
};

#endif // MAINSTATE_H
