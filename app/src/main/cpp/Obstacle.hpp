//
// Created by marc on 9/7/26.
//

#ifndef JUEGO_RAYLIB_OBSTACLE_HPP
#define JUEGO_RAYLIB_OBSTACLE_HPP
#include "raylib.h"

class Obstacle {
private:
    Color m_Color{BLACK};
    Vector2 m_Position{};
    float m_Size{5};

public:
    Obstacle(Vector2 position, float size) : m_Position(position), m_Size(size) {}

    Vector2 getPosition() const { return m_Position; }
    float getSize() const { return m_Size; }

    Vector2 getReflectedCollision(const Vector2& contactPoint, const Vector2& velocity) const;
    void draw();
};


#endif //JUEGO_RAYLIB_OBSTACLE_HPP
