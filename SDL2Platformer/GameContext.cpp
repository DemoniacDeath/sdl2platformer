#include "GameContext.h"

GameContext::GameContext(GameSettings * settings)
{
	this->settings = settings;
	if (!settings)
	{
		printf("Could not load game settings.");
		return;
	}

	window = SDL_CreateWindow(settings->name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, settings->windowWidth, settings->windowHeight, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}
	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void GameContext::free()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	delete settings;
	world->free();
	settings = NULL;
	window = NULL;
	renderer = NULL;
	world = NULL;
}
