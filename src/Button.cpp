//
// Created by marc on 8/7/26.
//

#include "Button.hpp"
#include "../external/raygui.h"

void Button::draw()
{
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(m_Color));
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
    m_Pressed = GuiButton(m_Rectangle, m_Text);
}

bool Button::isPressed()
{
    return m_Pressed;
}
