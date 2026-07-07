//
// Created by marc on 7/7/26.
//

#ifndef JUEGO_RAYLIB_GAMEMANAGER_HPP
#define JUEGO_RAYLIB_GAMEMANAGER_HPP
#include <memory>
#include <vector>
#include "Shape.hpp"


class GameManager {
public:
    std::shared_ptr<std::vector<Shape>> Shapes {std::make_shared<std::vector<Shape>>()};

    void update();
};

inline GameManager gameManager;

#endif //JUEGO_RAYLIB_GAMEMANAGER_HPP
