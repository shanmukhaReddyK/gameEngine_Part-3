#pragma once

#include "Scene.h"

class Scene_Menu : public Scene {

protected:
    std::vector<std::string>        m_menuStrings;
    std::vector<std::string>        m_levelPaths;
    std::optional<sf::Text>        m_menuText;
    std::string                     m_title;
    int                             m_selectedMenuIndex;

    void    init();
    void    sRender();
    void    sDoAction(const Action& action);
    void    onEnd();

public:
    void    update();
    Scene_Menu(GameEngine& gameEngine);
};