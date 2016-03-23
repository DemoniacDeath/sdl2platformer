#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <SDL2/SDL.h>
#include <math.h>

class Vector2D
{
    public:
        Vector2D();
        Vector2D(float, float);
        float length();
        Vector2D operator*(float);
        Vector2D operator/(float);
        Vector2D operator*=(float);
        Vector2D operator/=(float);
        Vector2D operator+(Vector2D);
        Vector2D operator-(Vector2D);
        Vector2D operator+=(Vector2D);
        Vector2D operator-=(Vector2D);

        float x = 0;
        float y = 0;
};

#endif // VECTOR2D_H
