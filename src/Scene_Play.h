#pragma once

#include "Scene.h"
#include <map>
#include <memory>

#include "EntityManager.hpp"

class Scene_Play : public Scene {

    struct PlayerConfig {
        float X,Y,CX,CY,SPEED,MAXSPEED,JUMP,GRAVITY;
        std::string WEAPON;
    };

protected:

    std::string                 m_levelPath;
    PlayerConfig                m_playerConfig;
    bool                        m_drawTextures=true;
    bool                        m_drawCollision=false;
    bool                        m_drawGrid=false;
    const Vec2f                 m_gridSize = {04,04};
    std::optional<sf::Text>     m_gridText;
    
    void init(const std::string& levelPath);

    void loadLevel(const std::string& filename);

    void update();
    void onEnd();
    void spawnPlayer();
    void spawnBullet(std::shared_ptr<Entity> entity);

    Vec2f gridToMidPixel(float x, float y, std::shared_ptr<Entity> entity);
    std::shared_ptr<Entity> player();

    void sDoAction(const Action& action);

    Scene_Play(GameEngine& gameEngine,const std::string& levelPath);

};