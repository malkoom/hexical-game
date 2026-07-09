//
// Created by marc on 8/7/26.
//

#ifndef JUEGO_RAYLIB_GAMEUIMANAGER_HPP
#define JUEGO_RAYLIB_GAMEUIMANAGER_HPP

#include "../scenes/Sprite.hpp"

class GameUIManager {
private:
    int m_Score{0};
    int m_Hearts{3};
    Sprite m_HeartSprite{"resources/images/heart.png", {10, 10}, 0.05f, GetColor(0xffffff88)};

public:
    void init();
    void draw();
    void update();
    void drawHearts();
    void drawScore();

    int getHearts() const { return m_Hearts; }
    void setHearts(int numHearts) { m_Hearts = numHearts; }
};

#endif //JUEGO_RAYLIB_GAMEUIMANAGER_HPP