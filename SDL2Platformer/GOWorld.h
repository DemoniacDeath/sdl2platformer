#ifndef GOWORLD_H
#define GOWORLD_H

#include "GameObject.h"
#include "Rect.h"
#include "GOCamera.h"

class GOWorld : public GameObject {
public:
    GOWorld(GameContext *, Rect);

    void handleEvent(SDL_Event *);

    void render();

    GOCamera *camera = NULL;
};

#endif // GOWORLD_H
