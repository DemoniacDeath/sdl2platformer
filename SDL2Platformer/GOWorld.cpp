#include "GOWorld.h"
#include "GameContext.h"


GOWorld::GOWorld(GameContext *context, Rect frame) : GameObject(context, frame) {
    camera = new GOCamera(context, frame);
}

void GOWorld::handleEvent(SDL_Event *e) {
    GameObject::handleEvent(e);
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
            case SDLK_q:
                context->quit = true;
                break;
        }
    }
}

void GOWorld::render() {
    GameObject::render(frame.center, camera->globalPosition(), camera->frame.size);
}

