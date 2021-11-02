#include <SDL2/SDL_timer.h>
#include "Animation.h"

Animation::Animation(Uint32 speed) {
    this->speed = speed;
    this->startTick = SDL_GetTicks();
}

Animation *Animation::animationWithSingleRenderObject(const RenderObject &renderObject) {
    auto *animation = new Animation(1);
    animation->addFrame(renderObject);
    return animation;
}

Animation *
Animation::animationWithSpeedAndTextureFile(Uint32 speed, SDL_Renderer *renderer, const std::string &filePath,
                                            int width,
                                            int height, Uint16 frames) {
    auto animation = new Animation(speed);
    SDL_Rect rect{0, 0, width, height};
    RenderObject renderObject = RenderObject::renderObjectFromFileWithFrame(renderer, filePath, rect);
    animation->addFrame(renderObject);
    for (Uint16 i = 1; i < frames; ++i) {
        RenderObject newRenderObject(renderObject);
        rect.y = i * rect.h;
        newRenderObject.renderFrameSize = rect;
        animation->addFrame(newRenderObject);
    }
    return animation;
}

void Animation::addFrame(const RenderObject &frame) {
    this->frames.push_back(frame);
}

void Animation::turnLeft(bool toTheLeft) {
    SDL_RendererFlip flip;
    if (toTheLeft && !turnedLeft) {
        flip = SDL_FLIP_HORIZONTAL;
        turnedLeft = true;
    } else if (!toTheLeft && turnedLeft) {
        flip = SDL_FLIP_NONE;
        turnedLeft = false;
    } else {
        return;
    }
    for (auto &frame: this->frames) {
        frame.renderFlip = flip;
    }
}

RenderObject Animation::animate() {
    Uint32 ticks = SDL_GetTicks();
    if (ticks - this->startTick >= this->frames.size() * this->speed) {
        this->startTick = ticks;
    }
    size_t frameIndex = (ticks - this->startTick) / this->speed;
    return this->frames[frameIndex];
}
