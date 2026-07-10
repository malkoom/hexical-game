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

void Shooter::draw(const Vector2& virtualMouse)
{
    if (m_IsAiming && m_CurrentShape)
    {
        Vector2 shapePos = m_CurrentShape->getPosition();

        float dist = Vector2Distance(shapePos, virtualMouse);
        float maxPullDistance = 400.0f;

        // Calculamos el ratio de fuerza entre 0.0f y 1.0f
        float forceRatio = Clamp(dist / maxPullDistance, 0.0f, 1.0f);


        Color color = {
            (unsigned char)(255 * forceRatio),          // Más rojo a más distancia
            (unsigned char)(255 * (1.0f - forceRatio)), // Menos verde a más distancia
            0,
            255
        };

        // Dibujamos la línea de tensión con el color calculado y la variable corregida
        DrawLineEx(shapePos, virtualMouse, 4.0f, color);

        //Un mini círculo neón en la punta del cursor para que se vea más arcade
        DrawCircleV(virtualMouse, 6.0f, color);
    }
}

void Shooter::setCurrentShape(Shape* shape)
{
    m_CurrentShape = shape;
}