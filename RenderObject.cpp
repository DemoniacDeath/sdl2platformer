#include <SDL2/SDL_image.h>
#include <iostream>
#include <utility>
#include "RenderObject.h"

RenderObject::RenderObject(std::shared_ptr<Texture> t) : texture{std::move(t)} {}

RenderObject RenderObject::renderObjectFromSurface(SDL_Renderer *renderer, SDL_Surface *surface) {
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, surface);
    if (t == nullptr) {
        throw std::runtime_error("Unable to create texture from surface! SDL Error: " + std::string(SDL_GetError()));
    }
    return RenderObject(std::make_shared<Texture>(t));
}

RenderObject RenderObject::renderObjectFromColor(SDL_Renderer *renderer, Color color) {
    SDL_Texture *t = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1,
                                       1);
    SDL_SetRenderTarget(renderer, t);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, nullptr);
    return RenderObject(std::make_shared<Texture>(t));
}

RenderObject RenderObject::renderObjectFromFile(SDL_Renderer *renderer, const std::string &path) {
    SDL_Texture *t = nullptr;
    SDL_Surface *surface = IMG_Load(path.data());
    if (surface == nullptr) {
        throw std::runtime_error("Unable to load image " + path + "! SDL_image Error: " + std::string(IMG_GetError()));
    }
    t = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (t == nullptr) {
        throw std::runtime_error(
                "Unable to create texture from " + path + "! SDL Error: " + std::string(SDL_GetError()));
    }
    return RenderObject(std::make_shared<Texture>(t));
}

RenderObject
RenderObject::renderObjectFromFileWithFrame(SDL_Renderer *renderer, const std::string &path, SDL_Rect frameSize) {
    RenderObject renderObject = RenderObject::renderObjectFromFile(renderer, path);
    renderObject.renderFrameSize = frameSize;
    renderObject.fullRender = false;
    return renderObject;
}

void
RenderObject::render(SDL_Renderer *renderer, const GameSettings &settings, Vector2D position, Size size,
                     Vector2D cameraPosition, Size cameraSize) {
    Vector2D renderPosition = position + Vector2D(-size.width / 2, -size.height / 2) - cameraPosition -
                              Vector2D(-cameraSize.width / 2, -cameraSize.height / 2);
    SDL_Rect rect;
    rect.x = (int) roundf(settings.windowWidth * (renderPosition.x / cameraSize.width));
    rect.y = (int) roundf(settings.windowHeight * (renderPosition.y / cameraSize.height));
    rect.w = (int) roundf(settings.windowWidth * (size.width / cameraSize.width));
    rect.h = (int) roundf(settings.windowHeight * (size.height / cameraSize.height));
    SDL_Rect *renderFrame = nullptr;
    if (!fullRender) {
        renderFrame = &renderFrameSize;
    }
    SDL_Texture *t = texture ? texture->getRawPointer() : nullptr;
    SDL_RenderCopyEx(renderer, t, renderFrame, &rect, 0, nullptr, renderFlip);
}
