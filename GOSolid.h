#ifndef GOSOLID_H
#define GOSOLID_H

#include "GameObject.h"
#include "Rect.h"
#include "Collision.h"

class GOSolid : public GameObject {
public:
    GOSolid(const GameContext&, Rect);

    void handleEnterCollision(Collision) override;

    void handleCollision(Collision) override;
};

#endif //GOSOLID_H
