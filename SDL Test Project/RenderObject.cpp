#include "RenderObject.h"
#include "GameContext.h"

RenderObject::RenderObject(GameContext * context, SDL_Texture * texture)
{
	this->context = context;
	this->texture = texture;
}

RenderObject::RenderObject(GameContext * context, SDL_Rect rect, Color color)
{
	texture = SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
	SDL_SetRenderTarget(context->renderer, texture);
	SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(context->renderer);
	SDL_SetRenderTarget(context->renderer, NULL);
	this->context = context;
}

void RenderObject::free()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
	context = NULL;
}