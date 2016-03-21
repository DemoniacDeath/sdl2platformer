#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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