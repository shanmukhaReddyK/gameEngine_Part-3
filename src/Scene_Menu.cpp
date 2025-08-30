#include"Action.hpp"
#include"Assets.hpp"
#include"Components.hpp"
#include"GameEngine.h"
#include"Scene_Menu.h"
#include"Scene_Play.h"

Scene_Menu::Scene_Menu(GameEngine& gameEngine) : Scene(gameEngine) {
    init();
}

void Scene_Menu::init() {
    registerAction(sf::Keyboard::Key::W, "UP");
    registerAction(sf::Keyboard::Key::S, "DOWN");
    registerAction(sf::Keyboard::Key::D, "PLAY");
    registerAction(sf::Keyboard::Key::Escape, "QUIT");

    m_title = "Sam samurai";
    m_menuStrings.push_back("Level 1");
    m_menuStrings.push_back("Level 2");
    m_menuStrings.push_back("Level 3");

    m_levelPaths.push_back("level1.txt");
    m_levelPaths.push_back("level2.txt");
    m_levelPaths.push_back("level3.txt");

    m_menuText=sf::Text(m_game.getAssets().getFont("Tech"));
    m_menuText->setCharacterSize(64);
}

void Scene_Menu::update() {
    m_entityManager.update();
    sRender();
}

void Scene_Menu::sDoAction(const Action& action) {
    if(action.type()=="START") {
        if(action.name()=="UP") {
            if(m_selectedMenuIndex>0) m_selectedMenuIndex--;

            else m_selectedMenuIndex=m_menuStrings.size()-1;
        }

        else if(action.name()=="DOWN") {
            m_selectedMenuIndex=(m_selectedMenuIndex+1) % m_menuStrings.size();
        }

        else if(action.name()=="PLAY") {
            m_game.changeScene("PLAY", std::make_shared<Scene_Play>(m_game, m_levelPaths[m_selectedMenuIndex]));
        }

        else if(action.name()=="QUIT") {
            onEnd();
        }
    }  
}

void Scene_Menu::sRender() {
    //set window to blue
    m_game.window().setView(m_game.window().getDefaultView());
    m_game.window().clear(sf::Color(100,100,255));

    //draw game title to the top of the  screen
    m_menuText->setCharacterSize(48);
    m_menuText->setString(m_title);
    m_menuText->setFillColor(sf::Color::Black);
    m_menuText->setPosition({10,10});
    m_game.window().draw(*m_menuText);

    //draw all the menu options
    for(size_t i =0; i<m_menuStrings.size();i++) {
        m_menuText->setString(m_menuStrings[i]);
        m_menuText->setFillColor(i==m_selectedMenuIndex ? sf::Color::Black : sf::Color::Blue);
        m_menuText->setPosition({10.f, 110.f + i * 72.f});
        m_game.window().draw(*m_menuText);
    }

    //draw the controls at the bottom-left
    m_menuText->setCharacterSize(20);
    m_menuText->setFillColor(sf::Color::Black);
    m_menuText->setString("up: w      down: s        play: d     quit: esc");
    m_menuText->setPosition({10,700});
    m_game.window().draw(*m_menuText);
    m_game.window().display();
}

void Scene_Menu::onEnd() {
    m_game.quit();
}
