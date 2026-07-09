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

    if (fabsf(m_Velocity.x) > 0.1f || fabsf(m_Velocity.y) > 0.1f) {
        Moving = true;
        for (auto& other : s_GameManager.Shapes) {

            if (&other == this) continue;

            if (CheckCollisionCircles(m_Position, m_Size, other.m_Position, other.m_Size)) {
                if (m_Type == other.m_Type) {
                    processCollisionWithEqualShape(other);
                } else {
                    processCollisionWithDifferentShape(other);
                }
            }
        }
    } else {
        if (Moving && !Pushed) s_GameManager.setHealth(s_GameManager.Health - 1); // No chocó con nadie
        m_Velocity = Vector2Zero();
        Moving = false;
        Pushed = false;
    }



    if (Dead) {
        s_GameManager.setHealth(0);
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
    shape.Pushed = true;

    return true;
}

bool Shape::processCollisionWithDifferentShape(Shape &shape)
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
    m_Velocity = Vector2Negate(m_Velocity);

    // Castigamos
    s_GameManager.setHealth(s_GameManager.Health - 1);

    return true;
}

void Shape::shoot(const Vector2 &releasePosition)
{
    Vector2 direction = Vector2Normalize(Vector2Subtract(m_Position, releasePosition));
    float distance = Vector2Distance(m_Position, releasePosition);
    float force = distance / 10.0f; // Ajusta este valor para cambiar la sensibilidad
    m_Velocity = Vector2Scale(direction, force);
}

void Shape::shatter()
{
}

void Shape::draw()
{
    Color baseColor = WHITE;
    int sides = 3;
    float rotation = 0.0f;

    switch (m_Type) {
        case(ShapeType::TRIANGLE):
            baseColor = GetColor(0x46425eff);
            sides = 3;
            rotation = 30.0f;
            break;
        case(ShapeType::SQUARE):
            baseColor = GetColor(0x15788cff);
            sides = 4;
            rotation = 45.0f;
            break;
        case(ShapeType::PENTAGON):
            baseColor = GetColor(0x00b9beff);
            sides = 5;
            rotation = 0.0f;
            break;
        case(ShapeType::HEXAGON):
            baseColor = GetColor(0xff6973ff);
            sides = 6;
            rotation = 0.0f;
            break;
        default:
            return;
    }
    DrawPoly(m_Position, sides, m_Size, rotation, ColorAlpha(baseColor, 0.7f));

    DrawPolyLinesEx(m_Position, sides, m_Size, rotation, 8.0f, ColorAlpha(baseColor, 0.3f));

    DrawPolyLinesEx(m_Position, sides, m_Size, rotation, 2.0f, baseColor);
}
