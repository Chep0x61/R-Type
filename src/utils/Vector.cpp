/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Vector
*/

#include "utils/Vector.hpp"

Vector2f::Vector2f(): x(0), y(0)
{
}

Vector2f::Vector2f(float posX, float posY): x(posX), y(posY)
{
}

Vector2f& Vector2f::operator=(const Vector2f vec)
{
    this->x = vec.x;
    this->y = vec.y;
    return *this;
}

bool Vector2f::operator==(const Vector2f vec) const
{
    return this->x == vec.x && this->y == vec.y;
}

bool Vector2f::operator!=(const Vector2f vec) const
{
    return !(this->x == vec.x && this->y == vec.y);
}

Vector2f Vector2f::operator+(const float nb) const
{
    return {this->x + nb, this->y + nb};
}

Vector2f Vector2f::operator-(const float nb) const
{
    return {this->x - nb, this->y - nb};
}

Vector2f Vector2f::operator+(const Vector2f vec) const
{
    return {this->x + vec.x, this->y + vec.y};
}

Vector2f Vector2f::operator-(const Vector2f vec) const
{
    return {this->x - vec.x, this->y - vec.y};
}