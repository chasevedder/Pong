#ifndef MAINMENU_H
#define MAINMENU_H

class GameStateManager;

#include "gamestate.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"


class MainMenu : public GameState
{
public:
    MainMenu();
    virtual ~MainMenu();
    virtual void update(GameStateManager* gsm, SDL_Event* event, SDL_Renderer* renderer, float deltaTime);
    virtual void render(SDL_Renderer *renderer, Uint8 alpha);
    virtual void onEnter(GameStateManager* gsm, SDL_Renderer* renderer);
    virtual void exit();

private:
    TTF_Font* titleFont;
    TTF_Font* optionsFont;

    static const int NUM_OPTS = 3;
    SDL_Texture* title;
    SDL_Texture* options[NUM_OPTS];

    SDL_Color colors[3];
    char* optionsText[NUM_OPTS];
    SDL_Rect pos[NUM_OPTS];
    bool selected[NUM_OPTS];
    bool visible[NUM_OPTS];

    SDL_Rect titleRect;
    SDL_Rect resumeRect;
    SDL_Rect quitRect;
};

#endif // MAINMENU_H
