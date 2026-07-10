//
// Created by marc on 8/7/26.
//

#ifndef JUEGO_RAYLIB_MENUSCENE_HPP
#define JUEGO_RAYLIB_MENUSCENE_HPP
#include "Scene.hpp"
#include "../Button.hpp"


class MenuScene : public Scene{
private:
    Button m_PlayBtn{ false, "Play", {1920 / 2, 1920 / 2}, {200, 100}, GRAY};
    Button m_ExitBtn{ false, "Quit", {1920 / 2, 1920 * 3 / 4}, {200, 100}, GRAY};

public:
    ~MenuScene() override = default;
    void init() override;
    void update(const Vector2 &virtualMouse) override;
    void draw(const Vector2 &virtualMouse) override;
    void drawUI(const Vector2 &virtualMouse) override;

};




#endif //JUEGO_RAYLIB_MENUSCENE_HPP
