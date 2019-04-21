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
    GOPlayer(GameContext *, Rect);

    void handleEvent(SDL_Event *);

    void handleKeyboard(const Uint8 *);

    void handleEnterCollision(Collision);

    void handleExitCollision(GameObject *);

    void handleCollision(Collision);

    void dealDamage(int);

    void die();

    void win();

    void free();

    float speed = 0.0f;
    float jumpSpeed = 0.0f;
    int power = 0;
    bool jumped = false;
    Size originalSize;
    bool crouched = false;
    int health;
    bool dead = false;
    bool won = false;

    Animation *idleAnimation = NULL;
    Animation *moveAnimation = NULL;
    Animation *jumpAnimation = NULL;
    Animation *crouchAnimation = NULL;
    Animation *crouchMoveAnimation = NULL;

    GOUIText *deathText = NULL;
    GOUIText *winText = NULL;
    GOUIBar *healthBar = NULL;
    GOUIBar *powerBar = NULL;

protected:
    void setCrouched(bool);
};

#endif // GOPLAYER_H
