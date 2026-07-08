//
// Created by marc on 7/7/26.
//

#ifndef JUEGO_RAYLIB_GAMEMANAGER_HPP
#define JUEGO_RAYLIB_GAMEMANAGER_HPP
#include <memory>
#include <vector>

#include "GameUIManager.hpp"
#include "../Shape.hpp"


class GameManager {
public:
    std::vector<Shape> Shapes {};
    GameUIManager UIManager{};

    void spawnShapes();
    void update();
};

inline GameManager s_GameManager;

#endif //JUEGO_RAYLIB_GAMEMANAGER_HPP
