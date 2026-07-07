//
// Created by marc on 7/7/26.
//

#ifndef JUEGO_RAYLIB_GAMESCENE_HPP
#define JUEGO_RAYLIB_GAMESCENE_HPP
#include <vector>
#include "Shape.hpp"
#include "Player.hpp"


class GameScene {
private:
    std::pmr::vector<Shape> m_Shapes;
    Player m_Player;

public:
    GameScene(Player player) : m_Player(player) {}

    void init();
    void update();
    void draw();
};


#endif //JUEGO_RAYLIB_GAMESCENE_HPP
