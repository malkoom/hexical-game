//
// Created by marc on 8/7/26.
//

#ifndef JUEGO_RAYLIB_SPRITE_HPP
#define JUEGO_RAYLIB_SPRITE_HPP

#include "raylib.h"

class Sprite {
private:
    Texture2D m_Texture;
    Vector2 m_Position{};
    float m_Scale{1.0f};

public:
    Sprite(const char* texturePath, Vector2 position, float scale);
    ~Sprite();

    void draw();
    void setPosition(const Vector2& position);
    Vector2 getPosition() const;
};

#endif //JUEGO_RAYLIB_SPRITE_HPP