#include <SDL2/SDL_image.h>
#include <stdexcept>
#include "GameContext.h"

GameContext::GameContext(GameSettings *s) {
    if (!s) {
        throw std::runtime_error("Could not load game settings.");
    }

    settings = s;

    window = SDL_CreateWindow(settings->name.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, settings->windowWidth,
                              settings->windowHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        throw std::runtime_error("Window could not be created! SDL Error: " + std::string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        throw std::runtime_error("Renderer could not be created! SDL Error: " + std::string(SDL_GetError()));
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

GameContext::~GameContext() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete ui;
    delete world;
    delete settings;
}
