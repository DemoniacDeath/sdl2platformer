#ifndef GOCAMERA_H
#define GOCAMERA_H

#include "GameObject.h"
#include "GOUIElement.h"
#include "GOUIText.h"
#include "GOUIBar.h"


class GOCamera : public GameObject
{
    public:
        GOCamera(GameContext *, Rect);
        void handleKeyboard(const Uint8 *);

        Size originalSize;
};

#endif // GOCAMERA_H
