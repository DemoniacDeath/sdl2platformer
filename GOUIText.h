#ifndef GOUITEXT_H
#define GOUITEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "GameObject.h"

class GOUIText : public GameObject {
public:
    GOUIText(const GameContext&, Rect);

    ~GOUIText() override;

    void setFont(const char *, int);

    void setText(std::string);

    void setColor(SDL_Color);

    void generate();

private:
    TTF_Font *font = nullptr;
    std::string text;
    SDL_Color color{0, 0, 0, 0};
};

#endif // GOUITEXT_H
