//
// Created by marc on 8/7/26.
//

#ifndef JUEGO_RAYLIB_MENUSCENE_HPP
#define JUEGO_RAYLIB_MENUSCENE_HPP
#include "Scene.hpp"
#include "../Button.hpp"
#include "managers/GameUIManager.hpp"

class MenuScene : public Scene{
private:
    Button m_PlayBtn{ false, "Play", {720 / 2, 720 / 2}, {400, 150}, GRAY};
    Button m_ExitBtn{ false, "Quit", {720 / 2, 720 * 3 / 4}, {400, 150}, GRAY};

public:
    ~MenuScene() override = default;
    void init() override;
    void update(const Vector2 &virtualMouse) override;
    void draw(const Vector2 &virtualMouse) override;
    void drawUI(const ScreenTransform& transform) override;

};




#endif //JUEGO_RAYLIB_MENUSCENE_HPP
