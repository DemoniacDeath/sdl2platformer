#include "Color.h"

Color::Color()
{
	r = g = b = a = 0;
}

Color::Color(Uint8 r, Uint8 g, Uint8 b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 0xFF;
}

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}