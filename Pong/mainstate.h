#ifndef MAINSTATE_H
#define MAINSTATE_H

#include "gamestate.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

class GameStateManager;


class MainState : public GameState
{
public:
    MainState();
    virtual ~MainState();
    virtual void onEnter(GameStateManager* gsm, SDL_Renderer* renderer);
    virtual void update(GameStateManager* gsm, SDL_Event* event);
    virtual void render(SDL_Renderer* renderer);
    virtual void exit();
};

#endif // MAINSTATE_H
