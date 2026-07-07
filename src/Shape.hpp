//
// Created by marc on 7/7/26.
//

#ifndef JUEGO_RAYLIB_SHAPE_HPP
#define JUEGO_RAYLIB_SHAPE_HPP

#include "raylib.h"

enum class ShapeType {
    TRIANGLE = 0,
    SQUARE,
    PENTAGON,
    HEXAGON
};

class Shape {
private:
    Vector2 m_Position{};
    ShapeType m_Type{ShapeType::TRIANGLE};
    float m_Size{3};
    float m_Speed {10};

public:
    Shape(Vector2 position, float size, float speed) : m_Position(position), m_Type(ShapeType::TRIANGLE), m_Size(size), m_Speed(speed) {}

    Vector2 getPosition() const {return this->m_Position;}
    float getSize() const {return this->m_Size;}
    float getSpeed() const {return this->m_Speed;}

    void setPosition(const Vector2& position) {this->m_Position = position;}
    void setSize(float size) {this->m_Size = size;}
    void setSpeed(float speed) {this->m_Speed = speed;}

    void update();
    void draw();

    bool processCollisionWithShape(Shape& shape);
    bool processCollisionWithBullet();
    void advanceShape() { m_Type = static_cast<ShapeType>((static_cast<int>(m_Type) + 1)); }
};


#endif //JUEGO_RAYLIB_SHAPE_HPP
