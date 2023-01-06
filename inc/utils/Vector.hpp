/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Vector hpp
*/
#pragma once

struct Vector2f {
    Vector2f();
    Vector2f(float posX, float posY);
    Vector2f(const Vector2f &vec)  = default;
    Vector2f& operator=(const Vector2f);
    bool operator==(const Vector2f vec) const;
    bool operator!=(const Vector2f vec) const;
    Vector2f operator+(const float nb) const;
    Vector2f operator-(const float nb) const;
    Vector2f operator+(const Vector2f vec) const;
    Vector2f operator-(const Vector2f vec) const;

    float x;
    float y;
};
