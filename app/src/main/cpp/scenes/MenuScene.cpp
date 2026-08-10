#include "MenuScene.hpp"
#include "../external/raygui.h"
#include "managers/SceneManager.hpp"
#include <math.h>
#include "raymath.h"

void MenuScene::init()
{
    GuiSetStyle(DEFAULT, TEXT_SIZE, 48);

    float virtualCenterX = 1920.0f / 2.0f;
    float virtualCenterY = 1920.0f / 2.0f;

    m_PlayBtn.setPosition({ virtualCenterX, virtualCenterY - 300.0f});
    m_VolumeButton.setPosition({ virtualCenterX, virtualCenterY });
    m_ExitBtn.setPosition({ virtualCenterX, virtualCenterY + 300.0f });
    m_TutorialBtn.setPosition({ 1700.0f, 100.0f });

    Color neonPink   = GetColor(0xff6973ff);
    Color neonCyan   = GetColor(0x00b9beff);
    Color darkBlue   = GetColor(0x46425eff);

    m_PlayBtn.setColor(neonPink);
    m_ExitBtn.setColor(neonCyan);
    m_VolumeButton.setColor(darkBlue);
    m_TutorialBtn.setColor(darkBlue);
}

void MenuScene::update(const Vector2 &virtualMouse)
{
    if (m_PlayBtn.isPressed()) {
        TraceLog(LOG_INFO, "Boton presionado");
        s_SceneManager.setCurrentScene(SceneType::GAME_SCENE);
    }

    if (m_ExitBtn.isPressed()) {
        s_SceneManager.Quit = true;
    }

    if (m_VolumeButton.isPressed()) {
        static bool volumeOn = true;
        volumeOn = !volumeOn;

        if (volumeOn) {
            m_VolumeButton.setText("Volume");
            SetMasterVolume(1.0f);
        } else {
            m_VolumeButton.setText("No Volume");
            SetMasterVolume(0.0f);
        }
    }

    if (m_TutorialBtn.isPressed()) {
        m_ShowTutorial = !m_ShowTutorial;
    }
}

void MenuScene::draw(const Vector2 &virtualMouse)
{
    static float timeAccumulator = 0.0f;
    timeAccumulator += GetFrameTime();

    static float baseRotation = 0.0f;
    float rotationSpeed = 15.0f + sinf(timeAccumulator * 0.5f) * 5.0f;
    baseRotation += rotationSpeed * GetFrameTime();
    if (baseRotation >= 360.0f) baseRotation -= 360.0f;

    float pulseFactor = 1.0f + sinf(timeAccumulator * 2.0f) * 0.08f;

    Vector2 absoluteCenter = { 1920.0f / 2.0f, 1920.0f / 2.0f };
    Vector2 targetOffset = {
        (virtualMouse.x - absoluteCenter.x) * 0.0f,
        (virtualMouse.y - absoluteCenter.y) * 0.0f
    };

    static Vector2 currentOffset = { 0.0f, 0.0f };
    currentOffset.x += (targetOffset.x - currentOffset.x) * 0.1f;
    currentOffset.y += (targetOffset.y - currentOffset.y) * 0.1f;
    Vector2 dynamicCenter = Vector2Add(absoluteCenter, currentOffset);

    Color colors[] = { GetColor(0xff6973ff), GetColor(0x00b9beff), GetColor(0x15788cff), GetColor(0x46425eff) };

    for (int p = 0; p < 40; p++) {
        float seedX = sinf((float)p * 452.13f) * 0.5f + 0.5f;
        float seedY = cosf((float)p * 983.57f) * 0.5f + 0.5f;
        float seedSize = sinf((float)timeAccumulator * 452.13f) * 0.5f + 0.5f;

        Vector2 starPos = { seedX * 1920.0f, seedY * 1920.0f };

        starPos.x += sinf(timeAccumulator + p) * 15.0f;
        starPos.y += cosf(timeAccumulator * 0.5f + p) * 15.0f;

        float starSize = 2.0f + seedSize * 8.0f;
        Color starColor = colors[p % 4];

        DrawCircleV(starPos, starSize, ColorAlpha(starColor, 0.7f));
    }

    float radius = 900.0f * pulseFactor;
    int i = 0;

    while (radius > 20.0f) {
        float currentRotation = baseRotation + (i * 8.0f) + (sinf(timeAccumulator) * 2.0f);
        float alphaFactor = (radius / (900.0f * pulseFactor));
        Color currentColor = colors[i % 4];

        DrawPolyLinesEx(
            dynamicCenter,
            6,
            radius,
            currentRotation,
            3.0f + (alphaFactor * 5.0f),
            ColorAlpha(currentColor, alphaFactor * 0.55f)
        );

        if (i % 2 == 0) {
            DrawPolyLinesEx(dynamicCenter, 6, radius + 4.0f, currentRotation, 1.0f, ColorAlpha(currentColor, alphaFactor * 0.35f));
        }

        radius -= 55.0f * pulseFactor;
        i++;
    }
}

void MenuScene::drawUI(const ScreenTransform& transform)
{
    GuiSetStyle(DEFAULT, TEXT_SIZE, (int)(48 * transform.scale));
    float time = (float)GetTime();

    const char* titleText = "HEXICAL";
    float baseFontSize = 160.0f;
    float baseSpacing = 12.0f;

    float finalFontSize = baseFontSize * transform.scale;
    float finalSpacing = baseSpacing * transform.scale;

    Vector2 textSize = MeasureTextEx(GetFontDefault(), titleText, finalFontSize, finalSpacing);

    Vector2 virtualCenterPos = { 1920.0f / 2.0f, 350.0f };

    Vector2 centerPos = {
        (virtualCenterPos.x * transform.scale) + transform.offset.x,
        (virtualCenterPos.y * transform.scale) + transform.offset.y
    };
    Vector2 origin = { textSize.x / 2.0f, textSize.y / 2.0f };

    Color neonPink   = GetColor(0xff6973ff);
    Color neonCyan   = GetColor(0x00b9beff);
    Color darkPurple = GetColor(0x46425eff);

    float pulse = sinf(time * 3.0f) * 10.0f * transform.scale;
    float baseRadius = (textSize.x / 2.0f) + (40.0f * transform.scale);
    float finalThickness = 3.0f * transform.scale;
    DrawPolyLinesEx(centerPos, 6, baseRadius + pulse, time * 10.0f, finalThickness, ColorAlpha(neonCyan, 0.2f));

    float shadowOffset = 6.0f * transform.scale;
    Vector2 shadowPos = { centerPos.x + shadowOffset, centerPos.y + shadowOffset };
    DrawTextPro(GetFontDefault(), titleText, shadowPos, origin, 0.0f, finalFontSize, finalSpacing, ColorAlpha(darkPurple, 0.5f));

    float glitchOffset = sinf(time * 20.0f) * cosf(time * 5.0f) * 4.0f * transform.scale;
    if (sinf(time * 10.0f) > 0.95f) glitchOffset *= 3.0f;

    Vector2 glitchPos = { centerPos.x - glitchOffset, centerPos.y };
    DrawTextPro(GetFontDefault(), titleText, glitchPos, origin, 0.0f, finalFontSize, finalSpacing, ColorAlpha(neonPink, 0.6f));

    DrawTextPro(GetFontDefault(), titleText, centerPos, origin, 0.0f, finalFontSize, finalSpacing, BLACK);

    const char* subText = "- GEOMETRIC MERGE GAME -";
    float baseSubFontSize = 35.0f;
    float baseSubSpacing = 4.0f;

    float finalSubFontSize = baseSubFontSize * transform.scale;
    float finalSubSpacing = baseSubSpacing * transform.scale;

    Vector2 subTextSize = MeasureTextEx(GetFontDefault(), subText, finalSubFontSize, finalSubSpacing);
    Vector2 subPos = { centerPos.x, centerPos.y + (textSize.y / 2.0f) + (40.0f * transform.scale) };
    Vector2 subOrigin = { subTextSize.x / 2.0f, subTextSize.y / 2.0f };

    float blink = sinf(time * 4.0f);
    Color subColor = (blink > 0.0f) ? neonPink : ColorAlpha(neonPink, 0.5f);

    DrawTextPro(GetFontDefault(), subText, subPos, subOrigin, 0.0f, finalSubFontSize, finalSubSpacing, subColor);

    m_PlayBtn.draw(transform);
    m_ExitBtn.draw(transform);
    m_VolumeButton.draw(transform);
    m_TutorialBtn.draw(transform);

    if (m_ShowTutorial) {
        drawTutorialWindow(transform);
    }
}

void MenuScene::drawTutorialWindow(const ScreenTransform& transform)
{
    // Definir dimensiones de la caja en espacio virtual (1920x1920) y escalar
    Rectangle virtualBox = { 1920.0f / 2.0f - 450.0f, 1920.0f / 2.0f - 350.0f, 900.0f, 700.0f };
    Rectangle scaledBox = {
        (virtualBox.x * transform.scale) + transform.offset.x,
        (virtualBox.y * transform.scale) + transform.offset.y,
        virtualBox.width * transform.scale,
        virtualBox.height * transform.scale
    };

    // Dibujar fondo opaco y borde neón
    DrawRectangleRec(scaledBox, GetColor(0x151224ff)); // Azul muy oscuro de fondo
    DrawRectangleLinesEx(scaledBox, 4.0f * transform.scale, GetColor(0x00b9beff)); // Borde Cyan

    // Dibujar el texto de forma manual
    int titleSize = (int)(48 * transform.scale);
    int bodySize = (int)(28 * transform.scale);

    // Título de la ventana
    DrawText("HOW TO PLAY", (int)(scaledBox.x + 40 * transform.scale), (int)(scaledBox.y + 40 * transform.scale), titleSize, GetColor(0xff6973ff));

    // Contenido de las instrucciones
    const char* line1 = "- Click + Drag: Aim & set power";
    const char* line2 = "- Release: Launch shape";
    const char* line3 = "- Right Click + Aiming: Cancel shot";
    const char* line4 = "- Match shapes to combine them and clear targets";
    const char* line5 = "- Avoid the obstacles or use them to line up shots";
    const char* line6 = "- Lose a life if you don't merge or hit a different shape!";


    float startY = scaledBox.y + 150 * transform.scale;
    float spacingY = 50 * transform.scale;

    DrawText(line1, (int)(scaledBox.x + 40 * transform.scale), (int)(startY), bodySize, RAYWHITE);
    DrawText(line2, (int)(scaledBox.x + 40 * transform.scale), (int)(startY + spacingY), bodySize, RAYWHITE);
    DrawText(line3, (int)(scaledBox.x + 40 * transform.scale), (int)(startY + spacingY * 2), bodySize, RAYWHITE);
    DrawText(line4, (int)(scaledBox.x + 40 * transform.scale), (int)(startY + spacingY * 5), bodySize, GetColor(0x00b9beff));
    DrawText(line5, (int)(scaledBox.x + 40 * transform.scale), (int)(startY + spacingY * 6), bodySize, GetColor(0x00b9beff));
    DrawText(line6, (int)(scaledBox.x + 40 * transform.scale), (int)(startY + spacingY * 7), bodySize, GetColor(0x00b9beff));

    // Botón de cierre
    Rectangle virtualCloseBtn = { virtualBox.x + virtualBox.width - 220.0f, virtualBox.y + virtualBox.height - 100.0f, 180.0f, 70.0f };
    Rectangle scaledCloseBtn = {
        (virtualCloseBtn.x * transform.scale) + transform.offset.x,
        (virtualCloseBtn.y * transform.scale) + transform.offset.y,
        virtualCloseBtn.width * transform.scale,
        virtualCloseBtn.height * transform.scale
    };

    int originalTextSize = GuiGetStyle(DEFAULT, TEXT_SIZE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, (int)(24 * transform.scale));

    if (GuiButton(scaledCloseBtn, "CLOSE")) {
        m_ShowTutorial = false;
    }

    GuiSetStyle(DEFAULT, TEXT_SIZE, originalTextSize);
}