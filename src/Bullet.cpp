//
// Created by marc on 7/7/26.
//

#include "Bullet.hpp"
#include "GameManager.hpp"

bool IsOutOfBounds(const Vector2& position, float radius = 0.0f);

void Bullet::update()
{
    if (Collided) return;

    if (IsOutOfBounds(m_Position, m_Size)) Collided = true;

    m_Position.x += m_Direction.x * m_Speed;
    m_Position.y += m_Direction.y * m_Speed;
    findCollisionWithShape(gameManager.Shapes);
}

void Bullet::draw()
{
    DrawCircleV(m_Position, m_Size, MAGENTA);
}

void Bullet::findCollisionWithShape(std::vector<Shape> &shapes)
{
    for (auto& shape : shapes) {
        if (CheckCollisionCircles(m_Position, m_Size, shape.getPosition(), shape.getSize())) {
            shape.processCollisionWithBullet();
            Collided = true;
        }
    }
}
