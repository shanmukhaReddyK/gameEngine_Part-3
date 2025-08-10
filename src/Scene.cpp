#include"GameEngine.h"
#include"Scene.h"

Scene::Scene(GameEngine& gameEngine) : m_game(gameEngine) {}  

void Scene::simulate(int frame) {
    while(frame--) {
        update();
    }
}

void Scene::doAction (const Action& action) {
    sDoAction(action); //? Think this might be the probable implementation of this function
}

void Scene::registerAction(const sf::Keyboard::Key& key, const std::string& name ) {
    m_actionMap[key]=name;

}

std::map<sf::Keyboard::Key,std::string>& Scene::getActionMap() {
    return m_actionMap;
}