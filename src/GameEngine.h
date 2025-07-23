#pragma once

#include<string>
#include<map>

class GameEngine {
    private:

    sf::RenderWindow                m_window;    //the window we will draw
    std::map<std::string,Scene>     m_scenes;
    Assets                          m_assets;

    std::string                     m_Currentscene;
    bool                            m_running;

    void init();

    public:

    void update();
    void run();
    void quit();
    void changeScene<T>();
    void sUserInput();
    
    Assets& getAssets();
    sf::Window& window(); 
}