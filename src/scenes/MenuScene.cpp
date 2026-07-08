//
// Created by marc on 8/7/26.
//

#include "MenuScene.hpp"
#include "../external/raygui.h"
#include "managers/SceneManager.hpp"

void MenuScene::init()
{
    GuiSetStyle(DEFAULT, TEXT_SIZE, 48); // Prueba con valores entre 40 y 60
}

void MenuScene::update(const Vector2 &virtualMouse)
{
    if (m_PlayBtn.isPressed()) {
        TraceLog(LOG_INFO, "Boton presionado");
        s_SceneManager.setCurrentScene(SceneType::GAME_SCENE);
    }
}

void MenuScene::draw(const Vector2 &virtualMouse)
{
    m_PlayBtn.draw();
}
