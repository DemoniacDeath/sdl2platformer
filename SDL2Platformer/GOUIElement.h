#ifndef GOUIELEMENT_H
#define GOUIELEMENT_H

#include "GameObject.h"

class GOUIElement : public GameObject
{
    public:
        GOUIElement(GameContext *, Rect);
};
#endif // GOUIELEMENT_H
