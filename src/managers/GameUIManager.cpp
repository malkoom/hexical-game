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

    if (m_Hexical) {
        drawHexical();
    }
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

void GameUIManager::drawHexical()
{
    const char* text = "HEXICAL";
    float spacing = 6.0f;

    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, m_FontScaler, spacing);

    Vector2 position = { 1920.0f / 2.0f, 1920.0f / 2.0f }; // Cambia a 1920 si volviste a ese tamaño

    Vector2 origin = { textSize.x / 2.0f, textSize.y / 2.0f };

    float rotation = 0.0f; // Modifica esto solo si quieres que el título gire

    DrawTextPro(
        GetFontDefault(),
        text,
        position,
        origin,
        rotation,
        m_FontScaler,
        spacing,
        ColorAlpha(RED, 0.5f) // Tu color translúcido neón (0xffffff88)
    );

    m_FontScaler += 5;
}

void GameUIManager::update()
{
}
