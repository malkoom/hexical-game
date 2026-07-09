//
// Created by marc on 7/7/26.
//

#include "Shooter.hpp"

#include "managers/GameManager.hpp"
#include <algorithm>

void Shooter::handleInput(const Vector2& virtualMouse)
{
    if (!m_CanShoot) return;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !m_IsAiming) {
        m_IsAiming = true;
        m_MousePressPosition = virtualMouse;

        for (auto& shape : s_GameManager.Shapes) {
            if (CheckCollisionPointCircle(virtualMouse, shape.getPosition(), shape.getSize())) {
                m_CurrentShape = &shape;
                break;
            } else {
                // Si llega aquí, gameManager.Shapes es nullptr
                TraceLog(LOG_ERROR, "ERROR: gameManager.Shapes es nullptr en Shooter::handleInput()!");
            }
        }
    }


    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && m_IsAiming)
    {
        m_IsAiming = false;
        if (m_CurrentShape)
        {
            m_CurrentShape->shoot(virtualMouse);
        }
    }
}

void Shooter::update()
{
   auto iter = std::find_if(s_GameManager.Shapes.begin(), s_GameManager.Shapes.end(),[](const Shape& shape) {
        return shape.Moving;
    });

    m_CanShoot = iter == s_GameManager.Shapes.end();
}

void Shooter::draw(const Vector2& virtualMouse)
{
    if (m_IsAiming && m_CurrentShape)
    {
        DrawLineEx(m_CurrentShape->getPosition(), virtualMouse, 2.0f, RED);
    }
}

void Shooter::setCurrentShape(Shape* shape)
{
    m_CurrentShape = shape;
}