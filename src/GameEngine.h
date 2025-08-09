#pragma once

#include<string>
#include<map>

#include"Assets.hpp"
#include"Scene.h"
#include"imgui.h"
#include"imgui-SFML.h"

class GameEngine {
    sf::RenderWindow                                m_window;    //the window we will draw
    std::map<std::string,std::shared_ptr<Scene>>    m_sceneMap;
    Assets                                          m_assets;
    std::string                                     m_currentScene;
    bool                                            m_running;

    void init(const std::string& assetConfig);

    public:

    void update();
    void run();
    void quit(); //TODO

   
    void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);
    void sUserInput();

    bool isRunning();
    
    Assets& getAssets();
    sf::RenderWindow& window();
    std::shared_ptr<Scene> currentScene();

    GameEngine(const std::string& assetConfig);
};