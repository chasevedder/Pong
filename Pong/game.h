#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "gamestatemanager.h"
#include "gamestate.h"

class Game : public GameStateManager
{
private:
    GameState* currentState;
    GameState* prevState;
    SDL_Event event;
public:
    Game();

    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;

    virtual ~Game();
    virtual void changeState(GameState* state);
    virtual GameState* getCurrentState();
    virtual GameState* getPrevState();
    virtual void update();
    void fpsCalc();
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // GAME_H
