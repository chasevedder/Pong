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
    virtual void update(GameStateManager* gsm, SDL_Event* event, SDL_Renderer* renderer);
    virtual void render(SDL_Renderer *renderer, Uint8 alpha);
    virtual void onEnter(GameStateManager* gsm, SDL_Renderer* renderer);
    virtual void exit();

private:
    TTF_Font* titleFont;
    TTF_Font* optionsFont;

    static const int NUM_OPTS = 2;
    SDL_Texture* title;
    SDL_Texture* options[NUM_OPTS];

    SDL_Color colors[3];
    char* optionsText[NUM_OPTS];
    SDL_Rect pos[NUM_OPTS];
    bool selected[NUM_OPTS];

    SDL_Rect titleRect;
    SDL_Rect resumeRect;
    SDL_Rect quitRect;

    SDL_Event event;
};

#endif // PAUSEMENU_H
