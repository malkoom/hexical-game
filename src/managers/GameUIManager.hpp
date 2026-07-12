// GameUIManager.hpp
#ifndef JUEGO_RAYLIB_GAMEUIMANAGER_HPP
#define JUEGO_RAYLIB_GAMEUIMANAGER_HPP

#include "../scenes/Sprite.hpp"
#include "../Button.hpp"

struct ScreenTransform {
    float scale;
    Vector2 offset;
};

class GameUIManager {
private:
    Button m_BackButton{false, "MENU", Vector2{1920/2, 75}, Vector2{200, 100}, RAYWHITE};

    int m_Score{0};
    int m_Hearts{0};
    Sprite m_HeartSprite{"resources/images/heart.png", {10, 10}, 0.05f, GetColor(0xffffff88)};

    float m_FontScaler{50};
    bool m_Hexical{false};

    void drawHexical(const ScreenTransform& transform);
    void drawHearts(const ScreenTransform& transform);
    void drawScore(const ScreenTransform& transform);

public:
    GameUIManager(int score, int hearts) : m_Score(score), m_Hearts(hearts) {}
    void init();
    void draw(const ScreenTransform& transform);
    void update();

    int getScore() const { return m_Score; }
    int getHearts() const { return m_Hearts; }
    bool getHexical() const { return m_Hexical; }

    void setScore(int score) { m_Score = score; }
    void setHearts(int numHearts) { m_Hearts = numHearts; }
    void setHexical(bool hexical) { m_Hexical = hexical; }
};

#endif //JUEGO_RAYLIB_GAMEUIMANAGER_HPP