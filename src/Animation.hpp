#pragma once

#include<string>
#include<SFML/Graphics.hpp>

#include"Vec2.hpp"

class Animation {
    sf::Sprite              m_sprite;
    Vec2f                   m_size;
    std::string             m_name;
    int                     m_frameCount;
    int                     m_currentFrame;
    int                     m_speed;

    public:
    void update() {
        m_currentFrame++;
        //TODO 1 Calculate the correct frame of the animation to ...
        //     2 set the texture rectangle properly(see con ....)
    } 

    bool hasEnded() const {
        //TODO detect when animation has ended (lst frame was ..)
        return false;
    } 

    const std::string& getName() const {
        return m_name;
    }

    const Vec2f& getSize() const {
        return m_size;
    }

    const sf::Sprite& getSprite() const  {
        return m_sprite;
    }
};