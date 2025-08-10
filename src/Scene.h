#pragma once

#include<map>

#include<Action.hpp>
#include<EntityManager.hpp>

class Scene {
protected:
  GameEngine&                                 m_game; //TODO: check if we have top do using raw pointers or there a better way to do it
  EntityManager                               m_entityManager;
  std::map<sf::Keyboard::Key,std::string>     m_actionMap;
  int                                         m_currentFrame;
  bool                                        m_paused;

public: 
  virtual void update() = 0;
  virtual void sDoAction(const Action&) = 0; //TODO: check if const Action& is the right way or we have to use samrt pointers or just Action
  virtual void sRender() = 0;
  
  void simulate(int frame);
  void doAction(const Action& action); //TODO: check if const Action& is the right way or we have to use smart pointers or just Action
  void registerAction(const sf::Keyboard::Key& key, const std::string& name ); //TODO: check if const Action& is the right way or we have to use samrt pointers or just Action
  
  std::map<sf::Keyboard::Key,std::string>& getActionMap();
  Scene(GameEngine& gameEngine);
};