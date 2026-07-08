//
// Created by marc on 7/7/26.
//

#include "Shooter.hpp"

#include "managers/GameManager.hpp"

void Shooter::handleInput(const Vector2& virtualMouse)
{
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
    // De momento no hace nada, pero podría usarse para actualizar el estado del shooter
}

void Shooter::draw(const Vector2& virtualMouse)
{
    if (m_IsAiming && m_CurrentShape)
    {
        DrawLineV(m_CurrentShape->getPosition(), virtualMouse, RED);
    }
}

void Shooter::setCurrentShape(Shape* shape)
{
    m_CurrentShape = shape;
}