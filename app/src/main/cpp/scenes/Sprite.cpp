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
    DrawTextureEx(m_Texture, m_Position, 0, 0.05* m_Scale, m_Color);
}