#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <SDL2/SDL.h>
#include "Color.h"
#include "Vector2D.h"
#include "Size.h"
#include "GameSettings.h"

class RenderObject {
public:
    RenderObject(SDL_Texture *texture);

    static RenderObject *renderObjectFromSurface(SDL_Renderer *, SDL_Surface *);

    static RenderObject *renderObjectFromColor(SDL_Renderer *, Color);

    static RenderObject *renderObjectFromFile(SDL_Renderer *, const char *);

    static RenderObject *renderObjectFromFileWithFrame(SDL_Renderer *, const char *, SDL_Rect);

    void render(SDL_Renderer *, GameSettings *, Vector2D, Size, Vector2D, Size);

    void free();

    SDL_Texture *texture = NULL;
    SDL_Rect renderFrameSize;
    SDL_RendererFlip renderFlip = SDL_FLIP_NONE;
    bool fullRender = true;
};

#endif // RENDEROBJECT_H
