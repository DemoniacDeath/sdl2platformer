#ifndef GOCAMERA_H
#define GOCAMERA_H

#include "GameObject.h"

class GOCamera : public GameObject {
public:
    GOCamera(const GameContext &, Rect);

    void handleKeyboard(const Uint8 *) override;

    Size originalSize;
};

#endif // GOCAMERA_H
