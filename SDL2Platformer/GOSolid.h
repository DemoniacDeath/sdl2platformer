#ifndef GOSOLID_H
#define GOSOLID_H

#include "GameObject.h"
#include "Rect.h"
#include "Collision.h"

class GOSolid : public GameObject {
public:
    GOSolid(GameContext *, Rect);

    void handleEnterCollision(Collision);

    void handleCollision(Collision);
};

#endif //GOSOLID_H
