#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameStateManager;
class SDL_Renderer;

//Game state base class
class GameState
{
    public:
        virtual void update(GameStateManager* gsm)=0;
        virtual void render(SDL_Renderer* renderer)=0;
        virtual void onEnter(GameStateManager* gsm)=0;
        virtual void exit()=0;
        virtual ~GameState(){}
};

#endif // GAMESTATE_H
