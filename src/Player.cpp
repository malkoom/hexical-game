//
// Created by marc on 7/7/26.
//

#include "Player.hpp"
#include "raymath.h"

void Player::draw()
{
    DrawCircleV(m_Position, m_Size, BLUE);
    DrawLineEx(m_Position, m_AimDirection, 6, YELLOW);
}

void Player::update()
{
    this->move();
}

void Player::move()
{
    Vector2 inputDirection = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_D)) inputDirection.x += 1.0f;
    if (IsKeyDown(KEY_A)) inputDirection.x -= 1.0f;
    if (IsKeyDown(KEY_W)) inputDirection.y -= 1.0f;
    if (IsKeyDown(KEY_S)) inputDirection.y += 1.0f;

    if (inputDirection.x != 0.0f || inputDirection.y != 0.0f) {
        // Normalizamos el vector de input para que andar en diagonal no te haga ir más rápido
        inputDirection = Vector2Normalize(inputDirection);

        // Movemos al jugador basándonos en la dirección normalizada y su velocidad
        m_Position.x += inputDirection.x * m_Speed;
        m_Position.y += inputDirection.y * m_Speed;

        // Calculamos la dirección del apuntado estirando el vector unitario a una longitud de 20 píxeles
        m_AimDirection.x = m_Position.x + (inputDirection.x * 20.0f);
        m_AimDirection.y = m_Position.y + (inputDirection.y * 20.0f);
    }
}

void Player::shoot()
{
}
