#pragma once
#include <SDL2/SDL.h>
#include "Color.h"
#include "Vector2D.h"
#include "Size.h"

class GameContext;
class GameObject;

class RenderObject
{
public:
	RenderObject(GameContext *, SDL_Texture *);
	static RenderObject * renderObjectFromColor(GameContext *, Color);
	static RenderObject * renderObjectFromFile(GameContext *, const char *);
	static RenderObject * renderObjectFromFileWithFrame(GameContext *, const char *, SDL_Rect);
	void render(GameContext *, Vector2D, Size, Vector2D, Size);
	void free();
	SDL_Texture * texture = NULL;
	SDL_Rect renderFrameSize;
	SDL_RendererFlip renderFlip = SDL_FLIP_NONE;
	bool fullRender = true;
};
