//
// Created by marc on 7/7/26.
//

#ifndef JUEGO_RAYLIB_GAMESCENE_HPP
#define JUEGO_RAYLIB_GAMESCENE_HPP

#include <vector>

#include "Scene.hpp"
#include "../Shape.hpp"
#include "../Shooter.hpp"

class GameScene : public Scene{
private:
    std::vector<Shape> m_Shapes;
    Shooter m_Shooter{};

public:
    ~GameScene() override = default;
    void init() override;
    void update(const Vector2& virtualMouse) override;
    void draw(const Vector2& virtualMouse) override;
};

#endif //JUEGO_RAYLIB_GAMESCENE_HPP