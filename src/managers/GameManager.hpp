//
// Created by marc on 7/7/26.
//

#ifndef JUEGO_RAYLIB_GAMEMANAGER_HPP
#define JUEGO_RAYLIB_GAMEMANAGER_HPP
#include <memory>
#include <vector>

#include "GameUIManager.hpp"
#include "Obstacle.hpp"
#include "../Shape.hpp"


class GameManager {
public:
    std::vector<Shape> Shapes {};
    std::vector<Obstacle> Obstacles{};
    GameUIManager UIManager{0, 0};
    int Health{3};
    int Score{0};
    int NumObstacles{2};

    void reset();
    void init();
    void update();

    void spawnShapes();
    void setHealth(int health) { Health = health; UIManager.setHearts(Health); };

};

inline GameManager s_GameManager;

#endif //JUEGO_RAYLIB_GAMEMANAGER_HPP
