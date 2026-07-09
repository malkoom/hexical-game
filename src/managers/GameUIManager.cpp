//
// Created by marc on 8/7/26.
//

#include "GameUIManager.hpp"
#include "../external/raygui.h"
#include <string>

void GameUIManager::init()
{
    m_HeartSprite.init();
}

void GameUIManager::draw()
{
    drawHearts();
    drawScore();
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

void GameUIManager::drawScore()
{
    GuiSetStyle(DEFAULT, TEXT_SIZE, 48);
    std::string scoreText = "Score: " + std::to_string(m_Score);
    DrawText(scoreText.c_str(), 1600, 50, 64, BLACK);
}

void GameUIManager::update()
{
}
