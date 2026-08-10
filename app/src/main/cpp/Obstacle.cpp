//
// Created by marc on 9/7/26.
//

#include "Obstacle.hpp"

#include "raymath.h"


Vector2 Obstacle::getReflectedCollision(const Vector2& contactPoint, const Vector2 &velocity) const
{
    Vector2 normal = Vector2Normalize(Vector2Subtract(contactPoint, m_Position));
    return Vector2Reflect(velocity, normal);
}

void Obstacle::draw()
{
    DrawCircleV(m_Position, m_Size, ColorAlpha(m_Color, 0.7f));

    for (float r = 0.0f; r < 8.0f; r += 2.0f) {
        DrawCircleLinesV(m_Position, m_Size + r, ColorAlpha(m_Color, 0.3f));
    }

    DrawCircleLinesV(m_Position, m_Size, m_Color);

}