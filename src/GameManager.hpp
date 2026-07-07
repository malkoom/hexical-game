//
// Created by marc on 7/7/26.
//

#ifndef JUEGO_RAYLIB_GAMEMANAGER_HPP
#define JUEGO_RAYLIB_GAMEMANAGER_HPP
#include <vector>
#include "Shape.hpp"


class GameManager {
public:
    std::vector<Shape> Shapes;

    void update();
};

inline GameManager gameManager;

#endif //JUEGO_RAYLIB_GAMEMANAGER_HPP
