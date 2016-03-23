#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "GameContext.h"

class Game
{
    public:
        void run();
    private:
        bool init();
        void exit();
        bool quit = false;
        GameContext * context = NULL;
};

#endif // GAME_H
