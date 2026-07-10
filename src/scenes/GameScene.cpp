//
// Created by marc on 7/7/26.
//

#include "GameScene.hpp"

#include <algorithm>

#include "../managers/GameManager.hpp"

void GameScene::init()
{
    // Inicializar m_Shapes para que apunte a un nuevo vector de Shape
    s_GameManager.reset();
    s_GameManager.init();
}

void GameScene::update(const Vector2& virtualMouse)
{
    m_Shooter.handleInput(virtualMouse);
    m_Shooter.update();

    s_GameManager.update();

}

void GameScene::draw(const Vector2& virtualMouse)
{
    for (auto& shape : s_GameManager.Shapes) {
        shape.draw();
    }

    for (auto& obstacle : s_GameManager.Obstacles) {
        obstacle.draw();
    }
}

void GameScene::drawUI(const ScreenTransform& transform)
{
    m_Shooter.draw(transform);
    s_GameManager.UIManager.draw(transform);
}