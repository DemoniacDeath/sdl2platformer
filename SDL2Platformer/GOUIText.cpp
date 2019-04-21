#include "GameContext.h"
#include "GOUIText.h"

GOUIText::GOUIText(GameContext *context, Rect frame) : GameObject(context, frame) {
}

void GOUIText::setFont(const char *path, int size) {
    font = TTF_OpenFont(path, size);
    generate();
}

void GOUIText::setText(std::string newText) {
    this->text = newText;
    generate();
}

void GOUIText::setColor(SDL_Color newColor) {
    this->color = newColor;
    generate();
}

void GOUIText::generate() {
    if (font && text.length()) {
        SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
        renderObject = RenderObject::renderObjectFromSurface(context->renderer, surface);
        SDL_FreeSurface(surface);
    }
}

