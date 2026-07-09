//
// Created by marc on 7/7/26.
//

#include "GameManager.hpp"
#include <ctime>
#include <algorithm>

#include "SceneManager.hpp"

void GameManager::reset()
{
    this->Shapes = {};
    UIManager = {};
    Health = {3};
}

void GameManager::init()
{
    spawnShapes();
    UIManager.init();
}

void GameManager::spawnShapes()
{

    int seed = (int)time(0);
    SetRandomSeed(seed);
    int shapeType = 0;

    for (int i = 0; i < 9; i++) {

        float x, y;
        bool collided{false};
        do {
            x = GetRandomValue(100, 1720);
            y = GetRandomValue(100, 1720);

            auto iter = std::find_if(Shapes.begin(), Shapes.end(), [x, y](Shape& shape) {
                    Vector2 point = { x, y };
                    return CheckCollisionPointCircle(point, shape.getPosition(), shape.getSize() + 100);
            });

            collided = iter != Shapes.end();

        } while (collided);


        Shapes.emplace_back(Vector2{x, y}, 50.0f, 10.0f, static_cast<ShapeType>(shapeType));

        if (i == 3) shapeType++;
        if (i == 7) shapeType++;
        if (i == 8) shapeType++;
    }
}

void GameManager::update()
{
    if (Health == 0) s_SceneManager.setCurrentScene(SceneType::GAME_SCENE);

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

