#ifndef PAUSEMENU_H
#define PAUSEMENU_H

class GameStateManager;
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "gamestate.h"

class PauseMenu : public GameState
{
public:
    PauseMenu();
    ~PauseMenu();
    virtual void update(GameStateManager* gsm, SDL_Event* event);
    virtual void render(SDL_Renderer *renderer);
    virtual void onEnter(GameStateManager* gsm, SDL_Renderer* renderer);
    virtual void exit();

private:
    TTF_Font *font;
    SDL_Color white;
    SDL_Surface* surf;
    SDL_Texture* message;
    SDL_Rect messageRect;
    SDL_Event event;
};

#endif // PAUSEMENU_H
