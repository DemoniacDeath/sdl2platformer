#include "GameContext.h"
#include "GOUIText.h"

GOUIText::GOUIText(const GameContext& context, Rect frame) : GameObject(context, frame)
{}

void GOUIText::setFont(const char *path, int size) {
    font = TTF_OpenFont(path, size);
}

void GOUIText::setText(std::string newText) {
    text = std::move(newText);
}

void GOUIText::setColor(SDL_Color newColor) {
    color = newColor;
}

void GOUIText::generate() {
    if (font && !text.empty()) {
        SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
        renderObject = RenderObject::renderObjectFromSurface(context.renderer, surface);
        SDL_FreeSurface(surface);
    }
}

GOUIText::~GOUIText()
{
    TTF_CloseFont(font);
}
