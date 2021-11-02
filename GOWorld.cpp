#include <algorithm>
#include "GOWorld.h"
#include "GameContext.h"

GOWorld::GOWorld(const GameContext &context, Rect frame) : GameObject(context, frame) {
    camera = std::make_unique<GOCamera>(context, frame);
}

void GOWorld::handleEvent(SDL_Event *e) {
    GameObject::handleEvent(e);
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
            case SDLK_q:
                context.quit = true;
                break;
        }
    }
}

void GOWorld::renderWorld() {
    render(frame.center, camera->globalPosition(), camera->frame.size);
}

void GOWorld::clean() {
    auto childrenEndRemove = children.end();
    auto childrenBeginRemove = std::remove_if(children.begin(), children.end(), [](const GameObject *child) {
        return child->removed;
    });
    children.erase(childrenBeginRemove, childrenEndRemove);

    for (auto i = blocks.begin(); i != blocks.end(); ++i) {
        if ((*i)->removed) {
            delete (*i);
            i = blocks.erase(i);
            if (i == blocks.end()) {
                break;
            }
        }
    }
}

GOWorld::~GOWorld() {
    for (auto block: blocks) {
        delete block;
    }
}
