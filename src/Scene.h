#pragma once

#include<map>

#include<Action.hpp>
#include<EntityManager.hpp>

class GameEngine;
class Scene {
protected:
  GameEngine&                                 m_game;
  EntityManager                               m_entityManager;
  std::map<sf::Keyboard::Key,std::string>     m_actionMap;
  int                                         m_currentFrame;
  bool                                        m_paused;

public: 
  virtual void update() = 0;
  virtual void sDoAction(const Action&) = 0;
  virtual void sRender() = 0;
  
  void simulate(int frame);
  void doAction(const Action& action);
  void registerAction(const sf::Keyboard::Key& key, const std::string& name );
  
  std::map<sf::Keyboard::Key,std::string>& getActionMap();
  Scene(GameEngine& gameEngine);
};