#include "sdltext.h"
#include "game.h"

SDLText::SDLText(std::string s, int size, int x, int y) {
    this->text = s;
    font = TTF_OpenFont("../resources/OpenSans-Regular.ttf", size);
    color = {255, 255, 255};
    surf = TTF_RenderText_Solid(font, text.c_str(), color);
    TTF_SizeText(font, text.c_str(), &pos.w, &pos.h);
    pos.x = x - (surf->w / 2);
    pos.y = y - (surf->h / 2);
    visible = true;
    selected = false;
}

SDLText::~SDLText() {
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    SDL_FreeSurface(surf);
}

std::string SDLText::getText() {
    return text;
}

void SDLText::setText(std::string s) {
    text = s;
    surf = TTF_RenderText_Solid(font, text.c_str(), color);
    TTF_SizeText(font, text.c_str(), &pos.w, &pos.h);
    texture = NULL;
}

void SDLText::render(SDL_Renderer *renderer) {
    if (texture == NULL) {
        texture = SDL_CreateTextureFromSurface(renderer, surf);
    }
    SDL_RenderCopy(renderer, texture, NULL, &pos);
}

void SDLText::setColor(SDL_Color color) {
    this->color = color;
    surf = TTF_RenderText_Solid(font, text.c_str(), color);
    TTF_SizeText(font, text.c_str(), &pos.w, &pos.h);
    texture = NULL;
}

SDL_Rect SDLText::getPos() {
    return pos;
}

