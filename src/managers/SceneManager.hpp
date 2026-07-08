//
// Created by marc on 8/7/26.
//

#ifndef JUEGO_RAYLIB_SCENEMANAGER_HPP
#define JUEGO_RAYLIB_SCENEMANAGER_HPP
#include <vector>
#include "scenes/Scene.hpp"

enum class SceneType {
    MENU_SCENE = 0,
    GAME_SCENE
};
class SceneManager {
private:
    SceneType m_CurrentScene;
    std::pmr::vector<Scene *> m_Scenes;
public:
    Scene* getCurrentScene()
    {
        return m_Scenes[(int)m_CurrentScene];
    }

    void setCurrentScene(SceneType newScene)
    {
        m_CurrentScene = newScene;
        m_Scenes[(int)m_CurrentScene]->init();
    }

    void pushScene(Scene * scene)
    {
        m_Scenes.push_back(scene);
    }

};

inline SceneManager s_SceneManager;


#endif //JUEGO_RAYLIB_SCENEMANAGER_HPP
