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
    m_PlayBtn.setPosition({(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2});
    m_ExitBtn.setPosition({(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 + 300});

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
    // Control del tiempo para efectos de parpadeo y animación sutil
    float time = (float)GetTime();

    // 1. CONFIGURACIÓN DE LA FUENTE Y PARÁMETROS
    const char* titleText = "HEXICAL";
    int fontSize = 160;       // Un tamaño imponente para el menú principal
    float spacing = 12.0f;    // Espaciado ancho de estilo futurista/industrial

    // Medimos el texto para poder centrarlo milimétricamente
    Vector2 textSize = MeasureTextEx(GetFontDefault(), titleText, (float)fontSize, spacing);
    Vector2 centerPos = { 1920.0f / 2.0f, 350.0f }; // Centrado horizontal, ubicado en la parte superior
    Vector2 origin = { textSize.x / 2.0f, textSize.y / 2.0f };

    // Paleta de colores neón sincronizada con tus figuras
    Color neonPink   = GetColor(0xff6973ff);
    Color neonCyan   = GetColor(0x00b9beff);
    Color darkPurple = GetColor(0x46425eff);

    // 2. EFECTO PULSO GEOMÉTRICO (Marco de fondo)
    // Un hexágono decorativo sutil detrás del texto que "respira"
    float pulse = sinf(time * 3.0f) * 10.0f;
    DrawPolyLinesEx(centerPos, 6, (textSize.x / 2.0f) + 40.0f + pulse, time * 10.0f, 3.0f, ColorAlpha(neonCyan, 0.2f));

    // 3. CAPA 1: Sombra Proyectada Estilo Glitch (Desplazada hacia abajo a la derecha)
    Vector2 shadowPos = { centerPos.x + 6.0f, centerPos.y + 6.0f };
    DrawTextPro(GetFontDefault(), titleText, shadowPos, origin, 0.0f, (float)fontSize, spacing, ColorAlpha(darkPurple, 0.5f));

    // 4. CAPA 2: Aberración Cromática Sutil (Efecto canal de color desfasado)
    // El texto rosa se desplaza horizontalmente imitando un fallo de monitor CRT
    float glitchOffset = sinf(time * 20.0f) * cosf(time * 5.0f) * 4.0f;
    // Solo hace el glitch fuerte de vez en cuando de forma matemática
    if (sinf(time * 10.0f) > 0.95f) glitchOffset *= 3.0f;

    Vector2 glitchPos = { centerPos.x - glitchOffset, centerPos.y };
    DrawTextPro(GetFontDefault(), titleText, glitchPos, origin, 0.0f, (float)fontSize, spacing, ColorAlpha(neonPink, 0.6f));

    // 5. CAPA 3: Texto Principal Hiper-Brillante
    // El color principal es un blanco roto translúcido que deja ver el entramado de fondo
    DrawTextPro(GetFontDefault(), titleText, centerPos, origin, 0.0f, (float)fontSize, spacing, BLACK);


    const char* subText = "- GEOMETRIC MERGE GAME -";
    int subFontSize = 35;
    float subSpacing = 4.0f;
    Vector2 subTextSize = MeasureTextEx(GetFontDefault(), subText, (float)subFontSize, subSpacing);
    Vector2 subPos = { centerPos.x, centerPos.y + (textSize.y / 2.0f) + 40.0f };
    Vector2 subOrigin = { subTextSize.x / 2.0f, subTextSize.y / 2.0f };


    float blink = sinf(time * 4.0f);
    Color subColor = (blink > 0.0f) ? neonPink : ColorAlpha(neonPink, 0.5f);

    DrawTextPro(GetFontDefault(), subText, subPos, subOrigin, 0.0f, (float)subFontSize, subSpacing, subColor);

    m_PlayBtn.draw();

    m_ExitBtn.draw();
}
