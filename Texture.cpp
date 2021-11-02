#include "Texture.h"

Texture::Texture(SDL_Texture *t) : texture{t} {}

Texture::~Texture() {
    SDL_DestroyTexture(texture);
}

SDL_Texture *Texture::getRawPointer() {
    return texture;
}
