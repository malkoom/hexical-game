//
// Created by marc on 8/7/26.
//

#include "Button.hpp"
#include "../external/raygui.h"

void Button::draw()
{
    m_Pressed = GuiButton(m_Rectangle, m_Text);
}

bool Button::isPressed()
{
    return m_Pressed;
}
