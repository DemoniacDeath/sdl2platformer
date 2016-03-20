#include "RenderObject.h"
#include "GameContext.h"
#include "GameObject.h"

RenderObject::RenderObject(GameContext * context, SDL_Texture * texture)
{
	this->texture = texture;
}

RenderObject::RenderObject(GameContext * context, GameObject * gameObject, Color color)
{
	texture = SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (int)gameObject->frame.size.width, (int)gameObject->frame.size.height);
	SDL_SetRenderTarget(context->renderer, texture);
	SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(context->renderer);
	SDL_SetRenderTarget(context->renderer, NULL);
}

void RenderObject::free()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
}