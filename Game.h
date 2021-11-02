#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <memory>
#include "GameContext.h"

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    GameContext *context = nullptr;
};

#endif // GAME_H
