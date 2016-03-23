#include "GOUIText.h"

GOUIText::GOUIText(GameContext * context, Rect frame) : GOUIElement::GOUIElement(context, frame)
{
};

void GOUIText::setFont(const char * path, int size)
{
    font = TTF_OpenFont(path, size);
    generate();
}

void GOUIText::setText(std::string text)
{
    this->text = text;
    generate();
}

void GOUIText::setColor(SDL_Color color)
{
    this->color = color;
    generate();
}

void GOUIText::generate()
{
    if (font && text.length())
    {
        SDL_Surface * surface = TTF_RenderText_Solid(font, text.c_str(), color);
        renderObject = RenderObject::renderObjectFromSurface(context, surface);
        SDL_FreeSurface(surface);
    }
}
