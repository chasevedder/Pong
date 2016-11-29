#ifndef SDLTEXT_H
#define SDLTEXT_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>;

class SDLText
{
public:
    SDLText(std::string text, int size, int x, int y);
    ~SDLText();
    void setText(std::string s);
    std::string getText();
    bool visible;
    bool selected;
    TTF_Font* font;
    void render(SDL_Renderer* renderer);
    void setColor(SDL_Color color);
    SDL_Rect getPos();
private:
    SDL_Texture* texture;
    SDL_Rect pos;
    std::string text;
    SDL_Surface* surf;
    SDL_Color color;
};

#endif // SDLTEXT_H
