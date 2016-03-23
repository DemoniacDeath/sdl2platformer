#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
#include "GameSettings.h"
#include "GOWorld.h"
#include "GOUI.h"

class GameContext
{
    public:
        GameContext(GameSettings *);
        void free();
        GameSettings * settings = NULL;
        SDL_Window * window = NULL;
        SDL_Renderer * renderer = NULL;
        GOWorld * world = NULL;
        GOUI * ui = NULL;
        bool quit = false;
};
#endif // GAMECONTEXT_H
