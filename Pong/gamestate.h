#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "SDL2/SDL.h"

class GameStateManager;
class SDL_Renderer;

//Game state base class
class GameState
{
    public:
        virtual void update(GameStateManager* gsm, SDL_Event* event, SDL_Renderer* renderer)=0;
        virtual void render(SDL_Renderer* renderer, Uint8 alpha)=0;
        virtual void onEnter(GameStateManager* gsm, SDL_Renderer* renderer)=0;
        virtual void exit()=0;
        virtual ~GameState(){}
};

#endif // GAMESTATE_H
