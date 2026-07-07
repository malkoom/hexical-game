//
// Created by marc on 7/7/26.
//

#include "GameScene.hpp"

#include <algorithm>

#include "GameManager.hpp"

void GameScene::init()
{
    // Inicializar m_Shapes para que apunte a un nuevo vector de Shape
    m_Shapes = gameManager.Shapes;

    m_Shapes->emplace_back(Shape({1920 / 4.0f, 1920 / 2.0f}, 50.0f, 10.0f));
    m_Shapes->emplace_back(Shape({1920 * 3.0f / 4.0f, 1920 / 2.0f}, 50.0f, 10.0f));
}

void GameScene::update(const Vector2& virtualMouse)
{
    m_Shooter.handleInput(virtualMouse);
    m_Shooter.update();

    m_Shapes->erase(
        std::remove_if(m_Shapes->begin(), m_Shapes->end(), [](const Shape& shape) {
            return shape.Collided;
        }),
        m_Shapes->end()
    );

    for (auto& shape : *m_Shapes)
    {
        shape.update();
    }
}

void GameScene::draw(const Vector2& virtualMouse)
{
    for (auto& shape : *m_Shapes)
    {
        shape.draw();
    }

    m_Shooter.draw(virtualMouse);
}