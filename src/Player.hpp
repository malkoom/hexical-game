//
// Created by marc on 7/7/26.
//

#ifndef JUEGO_RAYLIB_PLAYER_HPP
#define JUEGO_RAYLIB_PLAYER_HPP
#include "raylib.h"


class Player {
private:
    Vector2 m_Position{};
    Vector2 m_AimDirection{};
    float m_Size{3};
    float m_Speed {10};

public:
    Player(Vector2 position, float size, float speed) : m_Position(position), m_AimDirection(position), m_Size(size), m_Speed(speed) {}

    Vector2 getPosition() const {return this->m_Position;}
    float getSize() const {return this->m_Size;}
    float getSpeed() const {return this->m_Speed;}

    void setPosition(const Vector2& position) {this->m_Position = position;}
    void setSize(float size) {this->m_Size = size;}
    void setSpeed(float speed) {this->m_Speed = speed;}

    void update();
    void move();
    void shoot();
    void draw();
};


#endif //JUEGO_RAYLIB_PLAYER_HPP
