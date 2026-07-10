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

void MenuScene::drawUI(const Vector2 &virtualMouse)
{
    m_PlayBtn.draw();
    m_ExitBtn.draw();
}
