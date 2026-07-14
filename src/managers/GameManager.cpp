//
// Created by marc on 7/7/26.
//

#include "GameManager.hpp"
#include <ctime>
#include <algorithm>

#include "SceneManager.hpp"
#include "SoundManager.hpp"

void GameManager::reset()
{
    Shapes = {};
    Obstacles = {};
    UIManager = {s_GameManager.Score, s_GameManager.Health};
}

void GameManager::init()
{
    spawnShapes();
    UIManager.init();
}

void GameManager::update()
{
    // Reset si no tenemos vida
    if (Health == 0) {
        Score = 0;
        Health = 5;
        NumObstacles = 2;
        s_SoundManager.playSound("game-over");
        s_SceneManager.setCurrentScene(SceneType::GAME_SCENE);
    }

    // Borramos las muertas y las que han chocado
    Shapes.erase(
        std::remove_if(Shapes.begin(), Shapes.end(), [](const Shape& shape) {
            return shape.Dead || shape.Delete;
        }), Shapes.end()
    );

    if (Shapes.empty()) {
        Score++;
        Health += 2;
        NumObstacles++;
        s_SceneManager.setCurrentScene(SceneType::GAME_SCENE);
    }

    // Actualizamos las figuras
    for (auto& shape : Shapes)
    {
        if (shape.getType() > ShapeType::HEXAGON) {
            UIManager.setHexical(true);
            s_SoundManager.playSound("hexical");
        }
        shape.update();
    }

    // Actualizamos la UI
    UIManager.update();
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

    for (int i = 0; i < NumObstacles; i++) {

        float x, y;
        bool collided{false};
        do {
            x = GetRandomValue(300, 1600);
            y = GetRandomValue(100, 1720);

            auto iter = std::find_if(Shapes.begin(), Shapes.end(), [x, y](Shape& shape) {
                    Vector2 point = { x, y };
                    return CheckCollisionPointCircle(point, shape.getPosition(), shape.getSize() + 100);
            });

            collided = iter != Shapes.end();

        } while (collided);

        Obstacles.emplace_back(Vector2{x, y}, 100.0f);

    }
}

