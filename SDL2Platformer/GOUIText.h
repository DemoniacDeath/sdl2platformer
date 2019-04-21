#ifndef GOUITEXT_H
#define GOUITEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "GameObject.h"

class GOUIText : public GameObject {
public:
    GOUIText(GameContext *, Rect);

    void setFont(const char *, int);

    void setText(std::string);

    void setColor(SDL_Color);

    void generate();

protected:
    TTF_Font *font = NULL;
    std::string text;
    SDL_Color color;

};

#endif // GOUITEXT_H
