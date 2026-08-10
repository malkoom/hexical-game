#include "SoundManager.hpp"
#include <string>

void SoundManager::init()
{
    InitAudioDevice();
    SetMasterVolume(0.5f);

    m_SoundLibrary.emplace("pop", LoadSound("resources/sounds/pop.mp3"));
    m_SoundLibrary.emplace("miss", LoadSound("resources/sounds/miss.mp3"));
    m_SoundLibrary.emplace("game-over", LoadSound("resources/sounds/game-over.mp3"));
    m_SoundLibrary.emplace("swish", LoadSound("resources/sounds/swish.mp3"));
    m_SoundLibrary.emplace("minus-life", LoadSound("resources/sounds/minus-life.mp3"));
    m_SoundLibrary.emplace("hexical", LoadSound("resources/sounds/hexical.mp3"));
}

void SoundManager::kill()
{

    for (auto& pair : m_SoundLibrary) {
        UnloadSound(pair.second);
    }
    m_SoundLibrary.clear();

    CloseAudioDevice();
}

void SoundManager::playSound(const std::string& soundName)
{
    auto it = m_SoundLibrary.find(soundName);
    if (it != m_SoundLibrary.end()) {
        PlaySound(it->second);
    } else {
        TraceLog(LOG_WARNING, "SOUND: El sonido '%s' no existe en la librería", soundName.c_str());
    }
}