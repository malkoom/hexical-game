//
// Created by marc on 7/7/26.
//

#include "Shape.hpp"

#include "managers/GameManager.hpp"
#include "raymath.h"
#include "managers/GameManager.hpp"

bool IsOutOfBounds(const Vector2& position, float radius);

void Shape::update()
{
    if (Dead) return;

    m_Position = Vector2Add(m_Position, m_Velocity);
    m_Velocity = Vector2Scale(m_Velocity, m_Friction);

    if (IsOutOfBounds(m_Position, m_Size)) Dead = true;

    if (m_Velocity.x != 0.0f || m_Velocity.y != 0.0f) {

        for (auto& other : s_GameManager.Shapes) {

            if (&other == this) continue;

            if (CheckCollisionCircles(m_Position, m_Size, other.m_Position, other.m_Size)) {
                if (m_Type == other.m_Type) {
                    processCollisionWithEqualShape(other);
                    break;
                } else if (m_Type < other.m_Type){
                    // Lógica rebote
                }
            }
        }
    }
}

bool Shape::processCollisionWithEqualShape(Shape &shape)
{
    // Obtenemos el vector de distancia entre los dos centros
    Vector2 normal = Vector2Subtract(shape.m_Position, m_Position);
    float distance = Vector2Length(normal);

    // Evitamos división por cero si están exactamente en el mismo punto
    if (distance == 0.0f) return false;

    // Calculamos cuánto se están solapando (overlap)
    float overlap = (m_Size + shape.m_Size) - distance;

    if (overlap > 0.0f)
    {
        // Normalizamos el vector de dirección del choque
        normal = Vector2Scale(normal, 1.0f / distance);

        // Empujamos a esta figura hacia atrás la mitad del solapamiento
        m_Position = Vector2Subtract(m_Position, Vector2Scale(normal, overlap * 0.5f));
        // Empujamos a la otra figura hacia adelante la otra mitad
        shape.m_Position = Vector2Add(shape.m_Position, Vector2Scale(normal, overlap * 0.5f));
    }

    // Físicas
    // Al chocar, la otra gana la velocidad y esta la pierde
    shape.m_Velocity = m_Velocity;
    m_Velocity = Vector2Zero();

    // 3. Figura aumenta
    TraceLog(LOG_INFO, "¡Figuras separadas y colisión resuelta!");
    shape.advanceShape();

    this->Collided = true;

    return true;
}

void Shape::shoot(const Vector2 &releasePosition)
{
    Vector2 direction = Vector2Normalize(Vector2Subtract(m_Position, releasePosition));
    float distance = Vector2Distance(m_Position, releasePosition);
    float force = distance / 10.0f; // Ajusta este valor para cambiar la sensibilidad
    m_Velocity = Vector2Scale(direction, force);
}

void Shape::draw()
{
    switch (m_Type) {
        case(ShapeType::TRIANGLE):
            DrawTriangle({m_Position.x, m_Position.y - m_Size / 2.0f},
                {m_Position.x - m_Size / 2.0f, m_Position.y + m_Size / 2.0f},
                {m_Position.x + m_Size / 2.0f, m_Position.y + m_Size / 2.0f},
                GetColor(0x46425eff));
            break;
        case(ShapeType::SQUARE): {
            float halfSize = m_Size / 2.0f;  // Centro del cuadrado es el m_Position
            DrawRectangle(m_Position.x - halfSize, m_Position.y - halfSize, m_Size, m_Size, GetColor(0x15788cff));
        }
            break;
        case(ShapeType::PENTAGON):
            DrawPoly(m_Position, 5, m_Size, 0, GetColor(0x00b9beff));
            break;
        case(ShapeType::HEXAGON):
            DrawPoly(m_Position, 6, m_Size, 0, GetColor(0xff6973ff));
            break;
        default:
            break;
    }
}