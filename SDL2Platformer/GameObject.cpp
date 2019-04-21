#include "GameContext.h"
#include "GameObject.h"

GameObject::GameObject(GameContext *context) {
    this->context = context;
}

GameObject::GameObject(GameContext *context, Rect frame) {
    this->context = context;
    this->frame = frame;
}

GameObject::~GameObject() {
    free();
}

void GameObject::handleEvent(SDL_Event *e) {
    if (children.size()) {
        for (Uint32 i = 0, size = children.size(); i < size; i++) {
            children[i]->handleEvent(e);
        }
    }
}

void GameObject::handleKeyboard(const Uint8 *state) {
    if (children.size()) {
        for (Uint32 i = 0, size = children.size(); i < size; i++) {
            children[i]->handleKeyboard(state);
        }
    }
}

void GameObject::processPhysics() {
    if (physics)
        physics->change();

    if (children.size()) {
        for (Uint32 i = 0, size = children.size(); i < size; i++) {
            children[i]->processPhysics();
        }
    }
}

void GameObject::detectCollisions() {
    std::vector<GameObject *> *allColliders = new std::vector<GameObject *>;
    detectCollisions(allColliders);
    for (Uint32 i = 0, size = allColliders->size(); i < size; i++) {
        for (Uint32 j = i + 1; j < size; j++) {
            (*allColliders)[i]->physics->detectCollision((*allColliders)[j]->physics);
        }
    }
}

void GameObject::detectCollisions(std::vector<GameObject *> *allColliders) {
    if (physics)
        allColliders->push_back(this);
    for (Uint32 i = 0, size = children.size(); i < size; i++) {
        children[i]->detectCollisions(allColliders);
    }
}

void GameObject::handleEnterCollision(__attribute__((unused)) Collision collision) {}

void GameObject::handleExitCollision(__attribute__((unused)) GameObject *collider) {}

void GameObject::handleCollision(__attribute__((unused)) Collision collision) {}

void GameObject::animate() {
    if (animation) {
        this->renderObject = animation->animate();
    }
    for (Uint32 i = 0, size = children.size(); i < size; i++) {
        children[i]->animate();
    }
}

void GameObject::render(Vector2D localBasis, Vector2D cameraPosition, Size cameraSize) {
    if (visible && renderObject) {
        Vector2D globalPosition = frame.center;
        globalPosition += localBasis;
        renderObject->render(context->renderer, context->settings, globalPosition, frame.size, cameraPosition,
                             cameraSize);
    }
    if (children.size()) {
        for (Uint32 i = 0, size = children.size(); i < size; i++) {
            children[i]->render(localBasis + frame.center, cameraPosition, cameraSize);
        }
    }
}

void GameObject::addChild(GameObject *child) {
    children.push_back(child);
    child->parent = this;
}

void GameObject::clean() {
    if (children.size()) {
        for (std::vector<GameObject *>::const_iterator i = children.begin(); i != children.end(); ++i) {
            if ((*i)->removed) {
                delete *i;
                i = children.erase(i);
                if (i == children.end() || !children.size())
                    break;
            }
        }
    }
}

void GameObject::free() {
    if (!animation && renderObject) {
        renderObject->free();
        delete renderObject;
        renderObject = NULL;
    }

    if (animation) {
        animation->free();
        delete animation;
        animation = NULL;
    }

    if (physics)
        delete physics;

    if (children.size()) {
        std::vector<GameObject *>::const_iterator i = children.begin();
        while (i != children.end()) {
            delete (*i);
            //(*i)->parent = NULL;
            i++;
        }
        children.clear();
    }

    context = NULL;
}

Vector2D GameObject::globalPosition() {
    if (parent) {
        return frame.center + parent->globalPosition();
    } else {
        return frame.center;
    }
}
