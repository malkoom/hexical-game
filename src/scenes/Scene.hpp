//
// Created by marc on 8/7/26.
//

#ifndef JUEGO_RAYLIB_SCENE_HPP
#define JUEGO_RAYLIB_SCENE_HPP
#include "raylib.h"

class Scene {
public:
    virtual ~Scene() = default;

    virtual void init() = 0;
    virtual void update(const Vector2& virtualMouse) = 0;
    virtual void draw(const Vector2& virtualMouse) = 0;
};


#endif //JUEGO_RAYLIB_SCENE_HPP
