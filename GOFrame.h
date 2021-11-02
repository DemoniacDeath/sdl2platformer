#ifndef GOFRAME_H
#define GOFRAME_H

#include "GameObject.h"
#include "GOSolid.h"
#include "Rect.h"

class GOFrame : public GameObject {
public:
    GOFrame(const GameContext &, Rect, int);

    ~GOFrame() override;

    void addChildren();

    int width = 0;
    GOSolid *floor = nullptr;
    GOSolid *wallLeft = nullptr;
    GOSolid *wallRight = nullptr;
    GOSolid *ceiling = nullptr;
};

#endif // GOFRAME_H
