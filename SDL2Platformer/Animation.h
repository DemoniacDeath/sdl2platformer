#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include <vector>
#include "RenderObject.h"
#include "Color.h"

class Animation {
public:
    explicit Animation(Uint32);

    static Animation *animationWithSingleRenderObject(const RenderObject&);

    static Animation *animationWithSpeedAndTextureFile(Uint32, SDL_Renderer *, const std::string&, int, int, Uint16);

    void addFrame(const RenderObject&);

    void turnLeft(bool);

    RenderObject animate();

    std::vector<RenderObject> frames;
    Uint32 startTick = 0;
    Uint32 speed = 1;
    bool turnedLeft = false;
};

#endif // ANIMATION_H
