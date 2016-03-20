#pragma once
#include <SDL2/SDL.h>
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