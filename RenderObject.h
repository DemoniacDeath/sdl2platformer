#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <SDL2/SDL.h>
#include <memory>
#include "Color.h"
#include "Vector2D.h"
#include "Size.h"
#include "GameSettings.h"
#include "Texture.h"

class RenderObject {
public:
    RenderObject() = default;

    explicit RenderObject(std::shared_ptr<Texture>);

    RenderObject(const RenderObject &) = default;

    static RenderObject renderObjectFromSurface(SDL_Renderer *, SDL_Surface *);

    static RenderObject renderObjectFromColor(SDL_Renderer *, Color);

    static RenderObject renderObjectFromFile(SDL_Renderer *, const std::string &);

    static RenderObject renderObjectFromFileWithFrame(SDL_Renderer *, const std::string &, SDL_Rect);

    void render(SDL_Renderer *, const GameSettings &, Vector2D, Size, Vector2D, Size);

    std::shared_ptr<Texture> texture;
    SDL_Rect renderFrameSize = {0, 0, 0, 0};
    SDL_RendererFlip renderFlip = SDL_FLIP_NONE;
    bool fullRender = true;
};

#endif // RENDEROBJECT_H
