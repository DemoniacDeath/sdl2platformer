#ifndef GOPLAYER_H
#define GOPLAYER_H

#include <SDL2/SDL.h>
#include "GameObject.h"
#include "Rect.h"
#include "Collision.h"
#include "Animation.h"
#include "GOCamera.h"
#include "GOUIText.h"
#include "GOUIBar.h"

class GameContext;

class GOPlayer : public GameObject {
public:
    GOPlayer(const GameContext&, Rect);

    ~GOPlayer() override;

    void handleEvent(SDL_Event *) override;

    void handleKeyboard(const Uint8 *) override;

    void handleEnterCollision(Collision) override;

    void handleExitCollision(GameObject *) override;

    void handleCollision(Collision) override;

    void dealDamage(int);

    void die();

    void win();

    float speed = 0.0f;
    float jumpSpeed = 0.0f;
    int power = 0;
    bool jumped = false;
    Size originalSize;
    bool crouched = false;
    int health;
    bool dead = false;
    bool won = false;

    Animation *idleAnimation = nullptr;
    Animation *moveAnimation = nullptr;
    Animation *jumpAnimation = nullptr;
    Animation *crouchAnimation = nullptr;
    Animation *crouchMoveAnimation = nullptr;

    GOUIText *deathText = nullptr;
    GOUIText *winText = nullptr;
    GOUIBar *healthBar = nullptr;
    GOUIBar *powerBar = nullptr;

protected:
    void setCrouched(bool);
};

#endif // GOPLAYER_H
