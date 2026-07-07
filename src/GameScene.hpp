//
// Created by marc on 7/7/26.
//

#ifndef JUEGO_RAYLIB_GAMESCENE_HPP
#define JUEGO_RAYLIB_GAMESCENE_HPP

#include <vector>
#include <memory>
#include "Shape.hpp"
#include "Shooter.hpp"

class GameScene {
private:
    std::shared_ptr<std::vector<Shape>> m_Shapes;
    Shooter m_Shooter{};

public:
    void init();
    void update(const Vector2& virtualMouse);
    void draw(const Vector2& virtualMouse);
};

#endif //JUEGO_RAYLIB_GAMESCENE_HPP