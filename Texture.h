#ifndef SDL2PLATFORMER_TEXTURE_H
#define SDL2PLATFORMER_TEXTURE_H

#include <SDL2/SDL.h>

class Texture {
public:
    explicit Texture(SDL_Texture *);

    ~Texture();

    SDL_Texture *getRawPointer();

private:
    SDL_Texture *texture = nullptr;
};

#endif //SDL2PLATFORMER_TEXTURE_H
