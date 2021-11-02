#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>

class Color {
public:
    Color();

    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;
    Uint8 a = 0;
};

#endif // COLOR_H
