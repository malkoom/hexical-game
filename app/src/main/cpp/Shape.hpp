//
// Created by marc on 7/7/26.
//

#ifndef JUEGO_RAYLIB_SHAPE_HPP
#define JUEGO_RAYLIB_SHAPE_HPP

#include <vector>

#include "Obstacle.hpp"
#include "raylib.h"
#include "raymath.h"

enum class ShapeType {
    TRIANGLE = 0,
    SQUARE,
    PENTAGON,
    HEXAGON,
    HEXICAL
};

struct Fragment {
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float rotationSpeed;
    float size;
    float lifetime;
};

class Shape {
private:
    Color m_Color{WHITE};
    Vector2 m_Position{};
    Vector2 m_Direction{};
    Vector2 m_Velocity{};
    float m_Size{3};
    float m_Speed {10};
    float m_Friction{0.98f};
    bool m_Collided {false};
    ShapeType m_Type{ShapeType::TRIANGLE};
    std::vector<Fragment> m_Fragments;

public:

    bool Pushed{false};
    bool Dead {false};
    bool Moving {false};
    bool Delete{false};

    Shape(Vector2 position, float size, float speed, ShapeType shapeType = ShapeType::TRIANGLE) : m_Position(position), m_Type(shapeType), m_Size(size), m_Speed(speed), m_Velocity({0,0}) {}

    Vector2 getPosition() const {return this->m_Position;}
    Vector2 getVelocity() const {return this->m_Velocity;}
    float getSize() const {return this->m_Size;}
    float getSpeed() const {return this->m_Speed;}
    ShapeType getType() const {return this->m_Type;}


    void setPosition(const Vector2& position) {this->m_Position = position;}
    void setVelocity(const Vector2& velocity) {this->m_Velocity = velocity;}
    void setSize(float size) {this->m_Size = size;}
    void setSpeed(float speed) {this->m_Speed = speed;}
    void setType(ShapeType type) {this->m_Type = type;}


    void update();
    void draw();

    bool processCollisionWithEqualShape(Shape& shape);
    bool processCollisionWithDifferentShape(Shape& shape);
    void shoot(const Vector2& releasePosition);
    void advanceShape() { m_Type = static_cast<ShapeType>((static_cast<int>(m_Type) + 1)); }
    std::vector<Fragment> shatter();
};
#endif //JUEGO_RAYLIB_SHAPE_HPP