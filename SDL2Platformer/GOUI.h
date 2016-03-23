#ifndef GOUI_H
#define GOUI_H

#include "GOUIElement.h"

class GOUIBar;
class GOUIText;


class GOUI : public GOUIElement
{
    public:
        GOUI(GameContext *, Rect);
        void render();
        GOUIText * deathText = NULL;
        GOUIText * winText = NULL;
        GOUIElement * healthBarHolder = NULL;
        GOUIBar * healthBar = NULL;
        GOUIElement * powerBarHolder = NULL;
        GOUIBar * powerBar = NULL;
};

#endif // GOUI_H
