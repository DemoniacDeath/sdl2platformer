#pragma once
#include <SDL2/SDL.h>

class GameSettings
{
public:
	GameSettings();
	const char * name = NULL;
	int windowWidth = 0;
	int windowHeight = 0;
};
