#ifndef MULTIPLAYERSTATE_H
#define MULTIPLAYERSTATE_H

#include "gamestate.h"
#include "SDL2/SDL.h"
#include "enet/enet.h"
#include "paddle.h"

class GameStateManager;

class MultiplayerState : public GameState
{
public:
    MultiplayerState();
    ~MultiplayerState();
    virtual void update(GameStateManager* gsm, SDL_Event* event, SDL_Renderer* renderer, float deltaTime);
    virtual void render(SDL_Renderer *renderer, Uint8 alpha);
    virtual void onEnter(GameStateManager* gsm, SDL_Renderer* renderer);
    virtual void exit();

private:
    ENetAddress address;
    ENetHost *server;
    ENetEvent enetEvent;
    int serviceResult;
    Paddle* player;

};

#endif // MULTIPLAYERSTATE_H
