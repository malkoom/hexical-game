// GameUIManager.cpp
#include "GameUIManager.hpp"
#include "../external/raygui.h"
#include <string>

void GameUIManager::init()
{
    m_HeartSprite.init();
}

void GameUIManager::draw(const ScreenTransform& transform)
{
    drawHearts(transform);
    drawScore(transform);

    if (m_Hexical) {
        drawHexical(transform);
    }
}

void GameUIManager::drawHearts(const ScreenTransform& transform)
{
    Vector2 originalPosition = m_HeartSprite.getPosition();
    float spacing = 100.0f;

    for (int i = 0; i < m_Hearts; i++) {
        Vector2 heartVirtualPos = {originalPosition.x + (i * spacing), originalPosition.y};
        Vector2 heartScreenPos = {
            (heartVirtualPos.x * transform.scale) + transform.offset.x,
            (heartVirtualPos.y * transform.scale) + transform.offset.y
        };
        m_HeartSprite.setPosition(heartScreenPos);
        m_HeartSprite.draw();
    }

    m_HeartSprite.setPosition(originalPosition);
}

void GameUIManager::drawScore(const ScreenTransform& transform)
{
    GuiSetStyle(DEFAULT, TEXT_SIZE, (int)(48 * transform.scale));
    std::string scoreText = "Score: " + std::to_string(m_Score);

    Vector2 scoreVirtualPos = {1600.0f, 50.0f};
    Vector2 scoreScreenPos = {
        (scoreVirtualPos.x * transform.scale) + transform.offset.x,
        (scoreVirtualPos.y * transform.scale) + transform.offset.y
    };

    DrawText(scoreText.c_str(), (int)scoreScreenPos.x, (int)scoreScreenPos.y, (int)(64 * transform.scale), BLACK);
}

void GameUIManager::drawHexical(const ScreenTransform& transform)
{
    const char* text = "HEXICAL";
    float spacing = 6.0f;

    float scaledFontScaler = m_FontScaler * transform.scale;
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, scaledFontScaler, spacing * transform.scale);

    Vector2 positionVirtual = { 1920.0f / 2.0f, 1920.0f / 2.0f };
    Vector2 positionScreen = {
        (positionVirtual.x * transform.scale) + transform.offset.x,
        (positionVirtual.y * transform.scale) + transform.offset.y
    };

    Vector2 origin = { textSize.x / 2.0f, textSize.y / 2.0f };
    float rotation = 0.0f;

    DrawTextPro(
        GetFontDefault(),
        text,
        positionScreen,
        origin,
        rotation,
        scaledFontScaler,
        spacing * transform.scale,
        ColorAlpha(RED, 0.5f)
    );

    m_FontScaler += 5;
}

void GameUIManager::update()
{
}