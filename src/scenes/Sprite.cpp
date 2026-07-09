//
// Created by marc on 8/7/26.
//

#include "Sprite.hpp"


Sprite::~Sprite()
{
    UnloadTexture(m_Texture);
}

void Sprite::init()
{
    m_Texture = LoadTexture(m_TexturePath);
}

void Sprite::draw()
{
    DrawTextureEx(m_Texture, m_Position, 0, m_Scale, m_Color);
}

void Sprite::setPosition(const Vector2& position)
{
    m_Position = position;
}

Vector2 Sprite::getPosition() const
{
    return m_Position;
}