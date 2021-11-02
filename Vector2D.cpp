#include "Vector2D.h"

Vector2D::Vector2D() {
    x = y = 0;
}

Vector2D::Vector2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::operator*(float s) {
    return Vector2D(x * s, y * s);
}

Vector2D Vector2D::operator/(float s) {
    return Vector2D(x / s, y / s);
}

Vector2D Vector2D::operator*=(float s) {
    x *= s;
    y *= s;
    return *this;
}

Vector2D Vector2D::operator/=(float s) {
    x /= s;
    y /= s;
    return *this;
}

Vector2D Vector2D::operator+(Vector2D v) {
    return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::operator-(Vector2D v) {
    return Vector2D(x - v.x, y - v.y);
}

Vector2D Vector2D::operator+=(Vector2D v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector2D Vector2D::operator-=(Vector2D v) {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}