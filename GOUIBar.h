#ifndef GOUIBAR_H
#define GOUIBAR_H

#include "Rect.h"
#include "GameObject.h"

class GOUIBar : public GameObject {
public:
    GOUIBar(const GameContext &, Rect);

    void setValue(float);

protected:
    Rect originalFrame;
};

#endif // GOUIBAR_H
