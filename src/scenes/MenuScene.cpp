//
// Created by marc on 8/7/26.
//

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

    // Colocamos el botón de Play en todo el centro virtual
    m_PlayBtn.setPosition({ virtualCenterX, virtualCenterY });

    // El botón de salir 200 unidades virtuales más abajo
    m_ExitBtn.setPosition({ virtualCenterX, virtualCenterY + 300.0f });

    Color neonPink   = GetColor(0xff6973ff);
    Color neonCyan   = GetColor(0x00b9beff);

    m_PlayBtn.setColor(neonPink);
    m_ExitBtn.setColor(neonCyan);
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
}

void MenuScene::draw(const Vector2 &virtualMouse)
{
    // Control del tiempo global
    static float timeAccumulator = 0.0f;
    timeAccumulator += GetFrameTime();

    // Rotación base
    static float baseRotation = 0.0f;
    float rotationSpeed = 15.0f + sinf(timeAccumulator * 0.5f) * 5.0f; // Oscila entre 10 y 20 grados/seg
    baseRotation += rotationSpeed * GetFrameTime();
    if (baseRotation >= 360.0f) baseRotation -= 360.0f;

    // Pulso
    float pulseFactor = 1.0f + sinf(timeAccumulator * 2.0f) * 0.08f;

    // Interacción del raton
    Vector2 absoluteCenter = { 1920.0f / 2.0f, 1920.0f / 2.0f };
    Vector2 targetOffset = {
        (virtualMouse.x - absoluteCenter.x) * 0.08f,
        (virtualMouse.y - absoluteCenter.y) * 0.08f
    };

    // Lerp para que no sea brusco
    static Vector2 currentOffset = { 0.0f, 0.0f };
    currentOffset.x += (targetOffset.x - currentOffset.x) * 0.1f;
    currentOffset.y += (targetOffset.y - currentOffset.y) * 0.1f;
    Vector2 dynamicCenter = Vector2Add(absoluteCenter, currentOffset);

    // Particulas
    Color colors[] = { GetColor(0xff6973ff), GetColor(0x00b9beff), GetColor(0x15788cff), GetColor(0x46425eff) };

    for (int p = 0; p < 40; p++) {
        // Truco matemático para simular posiciones fijas pseudo-aleatorias
        float seedX = sinf((float)p * 452.13f) * 0.5f + 0.5f; // Rango 0..1
        float seedY = cosf((float)p * 983.57f) * 0.5f + 0.5f; // Rango 0..1
        float seedSize = sinf((float)timeAccumulator * 452.13f) * 0.5f + 0.5f; // Rango 0..1

        Vector2 starPos = { seedX * 1920.0f, seedY * 1920.0f };

        // Hacemos que floten flotando despacio en círculos diminutos
        starPos.x += sinf(timeAccumulator + p) * 15.0f;
        starPos.y += cosf(timeAccumulator * 0.5f + p) * 15.0f;

        float starSize = 2.0f + seedSize * 8.0f;
        Color starColor = colors[p % 4];

        // Las dibujamos muy translúcidas al fondo
        DrawCircleV(starPos, starSize, ColorAlpha(starColor, 0.7f));
    }

    // 5. RENDERIZADO DEL TÚNEL HEXAGONAL (Con pulso y descentrado)
    float radius = 900.0f * pulseFactor; // Aplicamos el pulso de tamaño general
    int i = 0;

    while (radius > 20.0f) {
        // Hacemos que las capas interiores roten cada vez más rápido para dar efecto de aceleración de agujero negro
        float currentRotation = baseRotation + (i * 8.0f) + (sinf(timeAccumulator) * 2.0f);

        // Factor de desvanecimiento hacia el centro
        float alphaFactor = (radius / (900.0f * pulseFactor));

        Color currentColor = colors[i % 4];

        // Dibuja el hexágono deformado suavemente hacia la posición del ratón
        DrawPolyLinesEx(
            dynamicCenter,
            6,
            radius,
            currentRotation,
            3.0f + (alphaFactor * 5.0f),
            ColorAlpha(currentColor, alphaFactor * 0.55f)
        );

        // Capa de brillo neón secundaria sutil adyacente
        if (i % 2 == 0) {
            DrawPolyLinesEx(dynamicCenter, 6, radius + 4.0f, currentRotation, 1.0f, ColorAlpha(currentColor, alphaFactor * 0.35f));
        }

        radius -= 55.0f * pulseFactor; // Escalonamiento afectado por el pulso
        i++;
    }
}

void MenuScene::drawUI(const ScreenTransform& transform)
{
    float time = (float)GetTime();

    const char* titleText = "HEXICAL";
    float baseFontSize = 160.0f;
    float baseSpacing = 12.0f;

    // Escalar tipografía a la resolución actual
    float finalFontSize = baseFontSize * transform.scale;
    float finalSpacing = baseSpacing * transform.scale;

    Vector2 textSize = MeasureTextEx(GetFontDefault(), titleText, finalFontSize, finalSpacing);

    // Mapear el centro virtual (1920x1920) a la pantalla física
    Vector2 virtualCenterPos = { 1920.0f / 2.0f, 350.0f };
    Vector2 centerPos = {
        (virtualCenterPos.x * transform.scale) + transform.offset.x,
        (virtualCenterPos.y * transform.scale) + transform.offset.y
    };
    Vector2 origin = { textSize.x / 2.0f, textSize.y / 2.0f };

    Color neonPink   = GetColor(0xff6973ff);
    Color neonCyan   = GetColor(0x00b9beff);
    Color darkPurple = GetColor(0x46425eff);

    // Hexágono de fondo latiendo en el centro
    float pulse = sinf(time * 3.0f) * 10.0f * transform.scale;
    float baseRadius = (textSize.x / 2.0f) + (40.0f * transform.scale);
    float finalThickness = 3.0f * transform.scale;
    DrawPolyLinesEx(centerPos, 6, baseRadius + pulse, time * 10.0f, finalThickness, ColorAlpha(neonCyan, 0.2f));

    // Capa 1: Sombra proyectada (estilo glitch oscuro)
    float shadowOffset = 6.0f * transform.scale;
    Vector2 shadowPos = { centerPos.x + shadowOffset, centerPos.y + shadowOffset };
    DrawTextPro(GetFontDefault(), titleText, shadowPos, origin, 0.0f, finalFontSize, finalSpacing, ColorAlpha(darkPurple, 0.5f));

    // Capa 2: Aberración cromática (desfase rosa emulando CRT)
    float glitchOffset = sinf(time * 20.0f) * cosf(time * 5.0f) * 4.0f * transform.scale;
    if (sinf(time * 10.0f) > 0.95f) glitchOffset *= 3.0f; // Pico de interferencia aleatorio

    Vector2 glitchPos = { centerPos.x - glitchOffset, centerPos.y };
    DrawTextPro(GetFontDefault(), titleText, glitchPos, origin, 0.0f, finalFontSize, finalSpacing, ColorAlpha(neonPink, 0.6f));

    // Capa 3: Texto principal
    DrawTextPro(GetFontDefault(), titleText, centerPos, origin, 0.0f, finalFontSize, finalSpacing, BLACK);

    // Subtítulo
    const char* subText = "- GEOMETRIC MERGE GAME -";
    float baseSubFontSize = 35.0f;
    float baseSubSpacing = 4.0f;

    float finalSubFontSize = baseSubFontSize * transform.scale;
    float finalSubSpacing = baseSubSpacing * transform.scale;

    Vector2 subTextSize = MeasureTextEx(GetFontDefault(), subText, finalSubFontSize, finalSubSpacing);
    Vector2 subPos = { centerPos.x, centerPos.y + (textSize.y / 2.0f) + (40.0f * transform.scale) };
    Vector2 subOrigin = { subTextSize.x / 2.0f, subTextSize.y / 2.0f };

    // Efecto parpadeo
    float blink = sinf(time * 4.0f);
    Color subColor = (blink > 0.0f) ? neonPink : ColorAlpha(neonPink, 0.5f);

    DrawTextPro(GetFontDefault(), subText, subPos, subOrigin, 0.0f, finalSubFontSize, finalSubSpacing, subColor);

    m_PlayBtn.draw(transform);
    m_ExitBtn.draw(transform);
}