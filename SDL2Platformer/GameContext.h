#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
#include "GameSettings.h"
#include "GOWorld.h"

class GameContext {
public:
	GameContext(GameSettings *);
	void free();
	GameSettings * settings = NULL;
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	GOWorld * world = NULL;
	bool quit = false;
};
