#include <SDL2/SDL_timer.h>
#include "Animation.h"

Animation::Animation(std::vector <RenderObject *> frames, Uint32 speed) : Animation::Animation(speed)
{
	this->frames = frames;
}

Animation::Animation(Uint32 speed)
{
	this->speed = speed;
	this->startTick = SDL_GetTicks();
}

void Animation::addFrame(RenderObject * frame)
{
	this->frames.push_back(frame);
}

RenderObject * Animation::animate()
{
	Uint32 ticks = SDL_GetTicks();
	if (ticks - this->startTick >= this->frames.size() * this->speed)
		this->startTick = ticks;
	size_t frameIndex = (ticks - this->startTick) / this->speed;
	return this->frames[frameIndex];
}

void Animation::free()
{
	for (Uint32 i = 0, size = this->frames.size(); i < size; i++)
	{
		this->frames[i]->free();
	}
}