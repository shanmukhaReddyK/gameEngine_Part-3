#include"GameEngine.h"
#include"Scene_Menu.h"
// #include"Scene_Play.h"

#include<iostream>

GameEngine::GameEngine(const std::string& assetConfig){
    init(assetConfig);
}

void GameEngine::init(const std::string& assetConfig){
    m_assets.loadFromfile(assetConfig);

    m_window.create(sf::VideoMode({1280,760}), "SFML_Window");
    m_window.setFramerateLimit(60);

    ImGui::SFML::Init(m_window);

    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale=2.0f;

    changeScene("MENU", std::make_shared<Scene_Menu>(*this));
}

void GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene) {  //? There might be some changes in this implementation
    if(endCurrentScene) {
        m_sceneMap.erase(m_currentScene);
    }
    
    m_currentScene=sceneName;
    
    if(m_sceneMap.find(sceneName)==m_sceneMap.end()) {
        m_sceneMap[sceneName]=scene;
    }
}

std::shared_ptr<Scene> GameEngine::currentScene(){
    return m_sceneMap[m_currentScene];
}

bool GameEngine::isRunning() {
    return m_running && m_window.isOpen();
}

sf::RenderWindow& GameEngine::window() {
    return m_window;
}

sf::Clock& GameEngine::clock() {
    return m_deltaClock;
}

void GameEngine::run() {
    while(isRunning()) {
        update();
    }
}

//Calls the update function of the current scene
void GameEngine::update() {
    
    currentScene()->update();
    sUserInput();
}

Assets& GameEngine::getAssets(){ //TODO: check weather should i use const or not
    return m_assets;
}

void GameEngine::sUserInput() {
    while (const auto event = m_window.pollEvent()) {
        ImGui::SFML::ProcessEvent(m_window, *event);
            
        if (event->is<sf::Event::Closed>())
            quit();

        if(event->is<sf::Event::KeyPressed>() || event->is<sf::Event::KeyReleased>()) {

            sf::Keyboard::Key key_code;

            if(auto const& key_pressed = event->getIf<sf::Event::KeyPressed>()) {
                key_code = key_pressed->code;
            }

            else if(auto const& key_released = event->getIf<sf::Event::KeyReleased>()) {
                key_code = key_released->code;
            }

            else {
                std::cout<< "NO ACTION IS ASSOCIATED WITH THIS KEY\n";
            }
        
            if(currentScene()->getActionMap().find(key_code)==currentScene()->getActionMap().end()) {
                continue;
            }

            const std::string actionType = (event->is<sf::Event::KeyPressed>()) ? "START" : "END";

            currentScene()->doAction(Action(currentScene()->getActionMap().at(key_code),actionType));
        }
        
    }
}

void GameEngine::quit() {
    m_running=false;
}
