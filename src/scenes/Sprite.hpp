//
// Created by marc on 8/7/26.
//

#ifndef JUEGO_RAYLIB_SPRITE_HPP
#define JUEGO_RAYLIB_SPRITE_HPP

#include "raylib.h"

class Sprite {
private:
    Texture2D m_Texture{};
    const char* m_TexturePath{};
    Vector2 m_Position{};
    float m_Scale{1.0f};
    Color m_Color{WHITE};


public:
    Sprite(const char* texturePath, Vector2 position, float scale, Color color = WHITE) :
    m_TexturePath(texturePath), m_Position(position), m_Scale(scale), m_Texture(), m_Color(color) {}
    ~Sprite();

    void init();
    void draw();
    void setPosition(const Vector2& position);
    Vector2 getPosition() const;
};

#endif //JUEGO_RAYLIB_SPRITE_HPP