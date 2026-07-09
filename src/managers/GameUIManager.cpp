//
// Created by marc on 8/7/26.
//

#include "GameUIManager.hpp"

void GameUIManager::init()
{
    m_HeartSprite.init();
}

void GameUIManager::draw()
{
    drawHearts();
}

void GameUIManager::drawHearts()
{
    Vector2 originalPosition = m_HeartSprite.getPosition();
    float spacing = 100.0f; // Espacio entre cada corazón

    for (int i = 0; i < m_Hearts; i++) {
        Vector2 heartPosition = {originalPosition.x + (i * spacing), originalPosition.y};
        m_HeartSprite.setPosition(heartPosition);
        m_HeartSprite.draw();
    }

    // Restauramos la posición original por si se necesita en otro sitio
    m_HeartSprite.setPosition(originalPosition);
}

void GameUIManager::update()
{
}