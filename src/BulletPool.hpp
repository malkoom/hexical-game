//
// Created by marc on 7/7/26.
//

#ifndef JUEGO_RAYLIB_BULLETPOOL_HPP
#define JUEGO_RAYLIB_BULLETPOOL_HPP
#include "Bullet.hpp"
#include <iostream>


class BulletPool {
private:
    int m_MaxBullets{10};
    Bullet* m_Bullets;
    int m_CurrentBullet{0};

public:
    BulletPool() : m_Bullets(new Bullet[m_MaxBullets]) {}

    Bullet* getBullet(const Vector2& newPos, const Vector2& newDir)
    {
        for (int i = 0; i < m_MaxBullets; i++) {
            if (!m_Bullets[i].Collided) {
                m_Bullets[i].reset(newPos, newDir);
                return &m_Bullets[i];
            }
        }

        std::cout << "Pool llena, no hay mas balas" << std::endl;
        return nullptr;
    }
};


#endif //JUEGO_RAYLIB_BULLETPOOL_HPP
