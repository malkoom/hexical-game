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
        m_CurrentShape = nullptr;
    }
}

void Shooter::update()
{
   auto iter = std::find_if(s_GameManager.Shapes.begin(), s_GameManager.Shapes.end(),[](const Shape& shape) {
        return shape.Moving;
    });

    m_CanShoot = iter == s_GameManager.Shapes.end();
}

void Shooter::draw(const ScreenTransform& transform)
{
    if (m_IsAiming && m_CurrentShape)
    {
        Vector2 shapeVirtualPos = m_CurrentShape->getPosition();
        Vector2 shapeScreenPos = {
            (shapeVirtualPos.x * transform.scale) + transform.offset.x,
            (shapeVirtualPos.y * transform.scale) + transform.offset.y
        };

        Vector2 mousePosition = GetMousePosition();

        float dist = Vector2Distance(shapeVirtualPos, mousePosition);
        float maxPullDistance = 400.0f;
        float forceRatio = Clamp(dist / maxPullDistance, 0.0f, 1.0f);

        Color color = {
            (unsigned char)(255 * forceRatio),
            (unsigned char)(255 * (1.0f - forceRatio)),
            0,
            255
        };

        float finalThickness = 4.0f * transform.scale;
        float finalRadius = 6.0f * transform.scale;

        DrawLineEx(shapeScreenPos, mousePosition, finalThickness, color);
        DrawCircleV(mousePosition, finalRadius, color);
    }
}
void Shooter::setCurrentShape(Shape* shape)
{
    m_CurrentShape = shape;
}