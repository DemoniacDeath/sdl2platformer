#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include <SDL2/SDL.h>
#include <cstdio>
#include <vector>
#include <bits/unique_ptr.h>
#include "GameSettings.h"
#include "GOWorld.h"

class GameContext {
public:
    explicit GameContext(GameSettings *);

    ~GameContext();

    GameSettings *settings = nullptr;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    GOWorld *world = nullptr;
    GameObject *ui = nullptr;
    mutable bool quit = false;
};

#endif // GAMECONTEXT_H
