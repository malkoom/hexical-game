//
// Created by marc on 8/7/26.
//

#include "Sprite.hpp"

Sprite::Sprite(const char* texturePath, Vector2 position, float scale)
    : m_Position(position), m_Scale(scale)
{
    m_Texture = LoadTexture(texturePath);
}

Sprite::~Sprite()
{
    UnloadTexture(m_Texture);
}

void Sprite::draw()
{
    DrawTextureEx(m_Texture, m_Position, 0, m_Scale, WHITE);
}

void Sprite::setPosition(const Vector2& position)
{
    m_Position = position;
}

Vector2 Sprite::getPosition() const
{
    return m_Position;
}