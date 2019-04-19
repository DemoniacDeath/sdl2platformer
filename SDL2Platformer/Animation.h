#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include <vector>
#include "RenderObject.h"
#include "Color.h"

class GameContext;

class Animation
{
    public:
        explicit Animation(Uint32);
        static Animation * animationWithSingleRenderObject(RenderObject *);
        static Animation * animationWithSpeedAndTextureFile(Uint32, GameContext *, const char *, int, int, Uint16);
        void addFrame(RenderObject *);
        void turnLeft(bool);
        RenderObject * animate();
        void free();
        std::vector <RenderObject *> frames;
        Uint32 startTick = 0;
        Uint32 speed = 1;
        bool turnedLeft = false;
};

#endif // ANIMATION_H
