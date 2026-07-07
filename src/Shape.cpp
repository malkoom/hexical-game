//
// Created by marc on 7/7/26.
//

#include "Shape.hpp"

void Shape::update()
{

}

bool Shape::processCollisionWithShape(Shape &shape)
{
    // Avanzamos las figuras
    this->advanceShape();
    shape.advanceShape();
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
