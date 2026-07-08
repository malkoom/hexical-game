//
// Created by marc on 8/7/26.
//

#ifndef JUEGO_RAYLIB_GAMEUIMANAGER_HPP
#define JUEGO_RAYLIB_GAMEUIMANAGER_HPP

#include "../scenes/Sprite.hpp"

class GameUIManager {
private:
    int m_Hearts{3};
    Sprite m_HeartSprite{"resources/heart.png", {10, 10}, 0.1f};

public:
    void draw();
    void update();
    void drawHearts();
};

#endif //JUEGO_RAYLIB_GAMEUIMANAGER_HPP