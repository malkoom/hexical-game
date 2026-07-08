//
// Created by marc on 8/7/26.
//

#include "GameUIManager.hpp"

void GameUIManager::draw()
{
    drawHearts();
}

void GameUIManager::drawHearts()
{
    float offset{};
    for (int i = 0; i < m_Hearts; i++) {
        m_HeartSprite.setPosition({m_HeartSprite.getPosition().x + offset, m_HeartSprite.getPosition().y});
        m_HeartSprite.draw();
        offset += 50;
    }
}

void GameUIManager::update()
{
}
