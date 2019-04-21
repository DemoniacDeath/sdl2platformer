#include <SDL2/SDL_image.h>
#include "RenderObject.h"
#include "GameContext.h"
#include "GameObject.h"

RenderObject::RenderObject(SDL_Texture *texture) {
    this->texture = texture;
}

RenderObject *RenderObject::renderObjectFromSurface(SDL_Renderer *renderer, SDL_Surface *surface) {
    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
        return NULL;
    }
    return new RenderObject(texture);
}

RenderObject *RenderObject::renderObjectFromColor(SDL_Renderer *renderer, Color color) {
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1,
                                             1);
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);
    return new RenderObject(texture);
}

RenderObject *RenderObject::renderObjectFromFile(SDL_Renderer *renderer, const char *path) {
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(path);
    if (surface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }
    SDL_FreeSurface(surface);
    return new RenderObject(texture);
}

RenderObject *
RenderObject::renderObjectFromFileWithFrame(SDL_Renderer *renderer, const char *path, SDL_Rect frameSize) {
    RenderObject *renderObject = RenderObject::renderObjectFromFile(renderer, path);
    if (!renderObject)
        return NULL;
    renderObject->renderFrameSize = frameSize;
    renderObject->fullRender = false;
    return renderObject;
}

void
RenderObject::render(SDL_Renderer *renderer, GameSettings *settings, Vector2D position, Size size,
                     Vector2D cameraPosition, Size cameraSize) {
    Vector2D renderPosition = position + Vector2D(-size.width / 2, -size.height / 2) - cameraPosition -
                              Vector2D(-cameraSize.width / 2, -cameraSize.height / 2);
    SDL_Rect rect;
    rect.x = (int) roundf(settings->windowWidth * (renderPosition.x / cameraSize.width));
    rect.y = (int) roundf(settings->windowHeight * (renderPosition.y / cameraSize.height));
    rect.w = (int) roundf(settings->windowWidth * (size.width / cameraSize.width));
    rect.h = (int) roundf(settings->windowHeight * (size.height / cameraSize.height));
    SDL_Rect *renderFrame = NULL;
    if (!fullRender)
        renderFrame = &renderFrameSize;
    SDL_RenderCopyEx(renderer, texture, renderFrame, &rect, 0, NULL, renderFlip);
}

void RenderObject::free() {
    SDL_DestroyTexture(texture);
    texture = NULL;
}
