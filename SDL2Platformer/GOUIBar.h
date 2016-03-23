#ifndef GOUIBAR_H
#define GOUIBAR_H

#include "GOUIElement.h"
#include "Rect.h"

class GOUIBar : public GOUIElement
{
    public:
        GOUIBar(GameContext *, Rect);
        void setValue(float);

    protected:
        float value = 100.f;
        Rect originalFrame;

};

#endif // GOUIBAR_H
