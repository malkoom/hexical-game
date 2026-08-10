//
// Created by marc on 11/7/26.
//

#ifndef JUEGO_RAYLIB_SOUNDMANAGER_HPP
#define JUEGO_RAYLIB_SOUNDMANAGER_HPP
#include <map>
#include <string>

#include "raylib.h"


class SoundManager {
private:
    std::map<std::string, Sound> m_SoundLibrary {};

public:


    void init();
    void kill();
    void playSound(const std::string& soundName);
};

inline SoundManager s_SoundManager{};


#endif //JUEGO_RAYLIB_SOUNDMANAGER_HPP
