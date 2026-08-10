//
// Created by marc on 8/7/26.
//

#include "Button.hpp"
#include "../external/raygui.h"
#include "managers/GameUIManager.hpp"

void Button::draw(const ScreenTransform& transform)
{
    // Escalar la caja del botón a coordenadas de pantalla física
    Rectangle scaledRect = {
        (m_Rectangle.x * transform.scale) + transform.offset.x,
        (m_Rectangle.y * transform.scale) + transform.offset.y,
        m_Rectangle.width * transform.scale,
        m_Rectangle.height * transform.scale
    };

    // Ajustar el tamaño de la fuente dinámicamente (guardando el tamaño base, por ejemplo, 20)
    int baseFontSize = 20;
    int finalFontSize = (int)(baseFontSize * transform.scale);
    if (finalFontSize < 10) finalFontSize = 10; // Evitar que colapse si la ventana es minúscula

    // Aplicar estilos a raygui
    GuiSetStyle(BUTTON, TEXT_SIZE, finalFontSize);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(m_Color));
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(BLACK));

    // Lanzar el botón con el rectángulo físico escalado
    m_Pressed = GuiButton(scaledRect, m_Text);
}

bool Button::isPressed()
{
    return m_Pressed;
}
