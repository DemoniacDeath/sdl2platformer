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
        static int renderThreadProcess(void *);
        GameContext * context = NULL;
        SDL_sem * contextLock = NULL;
        SDL_Thread * renderThread = NULL;
};

#endif // GAME_H
