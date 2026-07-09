//
// Created by marc on 7/7/26.
//

#ifndef JUEGO_RAYLIB_SHOOTER_HPP
#define JUEGO_RAYLIB_SHOOTER_HPP

#include "Shape.hpp"
#include "raylib.h"

class Shooter {
private:
    Shape* m_CurrentShape{nullptr};
    Vector2 m_MousePressPosition{};
    bool m_IsAiming{false};
    bool m_CanShoot{true};

public:
    void handleInput(const Vector2& virtualMouse);
    void update();
    void draw(const Vector2& virtualMouse);
    void setCurrentShape(Shape* shape);
};

#endif //JUEGO_RAYLIB_SHOOTER_HPP