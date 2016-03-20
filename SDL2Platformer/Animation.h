#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "RenderObject.h"

class Animation
{
public:
	Animation(std::vector <RenderObject *>, Uint32);
	Animation(Uint32);
	void addFrame(RenderObject *);
	RenderObject * animate();
	void free();
	std::vector <RenderObject *> frames;
	Uint32 startTick;
	Uint32 speed;
};

