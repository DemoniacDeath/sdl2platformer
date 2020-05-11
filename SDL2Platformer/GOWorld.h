#ifndef GOWORLD_H
#define GOWORLD_H

#include <memory>
#include "GameObject.h"
#include "Rect.h"
#include "GOCamera.h"

class GOWorld : public GameObject {
public:
    GOWorld(const GameContext&, Rect);

    ~GOWorld() override;

    void handleEvent(SDL_Event *) override;

    void renderWorld();

    void clean();

    std::unique_ptr<GOCamera> camera;

    std::unique_ptr<GameObject> healthBar;
    std::unique_ptr<GameObject> powerBar;

    std::vector<GameObject*> blocks;
};

#endif // GOWORLD_H
