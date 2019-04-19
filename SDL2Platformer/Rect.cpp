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

