#pragma once
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include "GameSettings.h"
#include "GOWorld.h"

class GameContext {
public:
	GameContext(GameSettings *);
	void free();
	GameSettings * settings;
	SDL_Window * window;
	SDL_Renderer * renderer;
	GOWorld * world;
	bool quit;
};
