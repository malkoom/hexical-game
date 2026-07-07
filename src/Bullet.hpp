//
// Created by marc on 7/7/26.
//

#ifndef JUEGO_RAYLIB_BULLET_HPP
#define JUEGO_RAYLIB_BULLET_HPP
#include "raylib.h"
#include "Shape.hpp"
#include <vector>


class Bullet {
private:
    Vector2 m_Position {};
    Vector2 m_Direction {};
    float m_Size {15};
    float m_Speed {20};


public:
    bool Collided {false};

    void reset(Vector2 position, Vector2 direction);
    void update();
    void draw();
    void findCollisionWithShape(std::vector<Shape>& shapes);
};


#endif //JUEGO_RAYLIB_BULLET_HPP
