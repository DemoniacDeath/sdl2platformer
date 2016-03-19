#include "Rect.h"

Rect::Rect()
{
	center = Vector2D();
	size = Size();
}

Rect::Rect(float x, float y, float w, float h)
{
	center = Vector2D(x, y);
	size = Size(w, h);
}

Rect::Rect(Vector2D center, Size size)
{
	this->center = center;
	this->size = size;
}

SDL_Rect Rect::SDLRect()
{
	SDL_Rect rect;
	rect.x = int(center.x - size.width / 2);
	rect.y = int(center.y - size.height / 2);
	rect.w = int(size.width);
	rect.h = int(size.height);
	return rect;
}