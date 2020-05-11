#ifndef GOCONSUMABLE_H
#define GOCONSUMABLE_H

#include "GameObject.h"

class GameContext;

class GOConsumable : public GameObject {
public:
    GOConsumable(const GameContext&, Rect);
};

#endif // GOCONSUMABLE_H
