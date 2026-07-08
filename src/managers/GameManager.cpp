//
// Created by marc on 7/7/26.
//

#include "GameManager.hpp"
#include <ctime>
#include <algorithm>

void GameManager::spawnShapes()
{

    int seed = (int)time(0);
    SetRandomSeed(seed);

    for (int i = 0; i < 10; i++) {
        float x = GetRandomValue(0, 1820);
        float y = GetRandomValue(0, 1820);

        Shapes.emplace_back(Vector2{x, y}, 50.0f, 10.0f, static_cast<ShapeType>(GetRandomValue(0, 3)));
    }
}

void GameManager::update()
{
    Shapes.erase(
        std::remove_if(Shapes.begin(), Shapes.end(), [](const Shape& shape) {
            return shape.Collided || shape.Dead;
        }),
        Shapes.end()
    );

    for (auto& shape : Shapes)
    {
        shape.update();
    }

    UIManager.update();
}