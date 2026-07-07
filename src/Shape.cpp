//
// Created by marc on 7/7/26.
//

#include "Shape.hpp"

#include "GameManager.hpp"
#include "raymath.h"
#include "GameManager.hpp"

void Shape::update()
{
    m_Position = Vector2Add(m_Position, m_Velocity);
    m_Velocity = Vector2Scale(m_Velocity, m_Friction);

    if (!Vector2Equals(m_Velocity, Vector2Zero())) {
        if (gameManager.Shapes) { // Añadir verificación de nullptr
            for (auto& other : *gameManager.Shapes) {

                if (&other == this) continue;

                if (CheckCollisionCircles(m_Position, m_Size, other.m_Position, other.m_Size))
                     processCollisionWithShape(other);
            }
        } else {
            // Si llega aquí, gameManager.Shapes es nullptr
            TraceLog(LOG_ERROR, "ERROR: gameManager.Shapes es nullptr en Shape::update()!");
        }
    }
}

bool Shape::processCollisionWithShape(Shape &shape)
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

    // 2. REACCIÓN DE FÍSICAS (Frenar o rebotar)
    // Al chocar, ambas pierden su velocidad inmediatamente para romper el bucle de movimiento
    m_Velocity = Vector2Zero();
    shape.m_Velocity = Vector2Zero();

    // 3. LÓGICA DEL JUEGO (Merge / Subir de nivel)
    TraceLog(LOG_INFO, "¡Figuras separadas y colisión resuelta!");

    // Aquí puedes llamar al operador ++ de tu enum para evolucionarla

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

bool Shape::processCollisionWithBullet()
{
    // Para simplificar todas las colisiones se evaluarán con círculos

}


void Shape::draw()
{
    switch (m_Type) {
        case(ShapeType::TRIANGLE):
            DrawTriangle({m_Position.x, m_Position.y - m_Size / 2.0f},
                {m_Position.x - m_Size / 2.0f, m_Position.y + m_Size / 2.0f},
                {m_Position.x + m_Size / 2.0f, m_Position.y + m_Size / 2.0f},
                DARKGREEN);
            break;
        case(ShapeType::SQUARE):
            float halfSize = m_Size / 2.0f;  // Centro del cuadrado es el m_Position
            DrawRectangle(m_Position.x - halfSize, m_Position.y - halfSize, m_Size, m_Size, DARKPURPLE);
            break;
    }
}