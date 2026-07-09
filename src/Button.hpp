//
// Created by marc on 8/7/26.
//

#ifndef JUEGO_RAYLIB_BUTTON_HPP
#define JUEGO_RAYLIB_BUTTON_HPP
#include "raylib.h"

class Button {
private:
    bool m_Pressed;
    char * m_Text;
    Rectangle m_Rectangle;

public:
    Button(bool m_pressed, char *m_text, const Vector2 &m_position, const Vector2 &m_size, const Color &m_color)
        : m_Pressed(m_pressed),
          m_Text(m_text),
          m_Rectangle({m_position.x - m_size.x / 2, m_position.y - m_size.y / 2, m_size.x, m_size.y}),
          m_Color(m_color)
    {
    }

    ~Button() = default;

    Vector2 getPosition() const { return {m_Rectangle.x + m_Rectangle.width / 2, m_Rectangle.y + m_Rectangle.height / 2};}

    void setPosition(const Vector2 &position) { m_Rectangle.x = position.x - m_Rectangle.width / 2; m_Rectangle.y = position.y - m_Rectangle.height / 2;};
    void setSize(const Vector2 &size);

    void draw();
    bool isPressed();

private:
    Color m_Color;

};


#endif //JUEGO_RAYLIB_BUTTON_HPP
