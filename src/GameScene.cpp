//
// Created by marc on 7/7/26.
//

#include "GameScene.hpp"

#include <iostream>

void GameScene::init()
{
    std::cout << "Iniciando el juego";
    // Primeras Formas
    m_Shapes.emplace_back((Vector2){200, 400}, 20, 10);
    m_Shapes.emplace_back((Vector2){400, 200}, 20, 10);
}

void GameScene::update()
{
    m_Player.update();

    for (auto& shape : m_Shapes) {
        shape.update();
    }
}

void GameScene::draw()
{
    m_Player.draw();

    for (auto& shape : m_Shapes) {
        shape.draw();
    }
}
