//
// Created by marc on 10/8/26.
//
#include "raylib.h"

bool IsOutOfBounds(const Vector2& position, float radius) {
    return (position.x + radius < 0 || position.x - radius > 1920 ||
            position.y + radius < 0 || position.y - radius > 1920);
}