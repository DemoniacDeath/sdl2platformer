#pragma once
#include <SDL2/SDL.h>

class GameSettings
{
public:
	GameSettings();
	const char * name;
	int windowWidth;
	int windowHeight;
};
