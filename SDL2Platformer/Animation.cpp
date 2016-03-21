#include <SDL2/SDL_timer.h>
#include "Animation.h"
#include "GameContext.h"

Animation::Animation(std::vector <RenderObject *> frames, Uint32 speed) : Animation::Animation(speed)
{
	this->frames = frames;
}

Animation::Animation(Uint32 speed)
{
	this->speed = speed;
	this->startTick = SDL_GetTicks();
}

Animation * Animation::animationWithSingleRenderObject(RenderObject * renderObject)
{
	Animation * animation = new Animation(1);
	animation->addFrame(renderObject);
	return animation;
}

Animation * Animation::animationWithSpeedAndColor(Uint32 speed, GameContext * context, Color color)
{
	Animation * animation = new Animation(speed);
	animation->addFrame(RenderObject::renderObjectFromColor(context, color));
	animation->addFrame(RenderObject::renderObjectFromColor(context, Color(0x00, 0x00, 0x00, 0xFF)));
	return animation;
}

Animation * Animation::animationWithSpeedAndTextureFile(Uint32 speed, GameContext * context, const char * filePath, int width, int height, Uint16 frames)
{
	Animation * animation = new Animation(speed);
	SDL_Rect rect;
	rect.w = width;
	rect.h = height;
	rect.x = 0;
	rect.y = 0;
	RenderObject * renderObject = RenderObject::renderObjectFromFileWithFrame(context, filePath, rect);
	animation->addFrame(renderObject);
	for (Uint16 i = 1; i < frames; i++)
	{
		RenderObject * newRenderObject = new RenderObject(*renderObject);
		rect.y = i*rect.h;
		newRenderObject->renderFrameSize = rect;
		animation->addFrame(newRenderObject);
	}
	return animation;
}

void Animation::addFrame(RenderObject * frame)
{
	this->frames.push_back(frame);
}

void Animation::turnLeft(bool toTheLeft)
{
	SDL_RendererFlip flip;
	if (toTheLeft && !turnedLeft)
	{
		flip = SDL_FLIP_HORIZONTAL;
		turnedLeft = true;
	}
	else if (!toTheLeft && turnedLeft)
	{
		flip = SDL_FLIP_NONE;
		turnedLeft = false;
	}
	else
		return;
	for (Uint32 i = 0, size = this->frames.size(); i < size; i++)
	{
		this->frames[i]->renderFlip = flip;
	}
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