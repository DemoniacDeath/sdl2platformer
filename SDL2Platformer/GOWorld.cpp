#include "GOWorld.h"
#include "GameContext.h"


GOWorld::GOWorld(GameContext * context, SDL_Rect rect) : GameObject(context, rect) {};

void GOWorld::handleEvent(SDL_Event * e)
{
	GameObject::handleEvent(e);
	if (e->type == SDL_KEYDOWN)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_q:
			context->quit = true;
			break;
		}
	}
}