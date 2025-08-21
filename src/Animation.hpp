#pragma once

#include<string>
#include<SFML/Graphics.hpp>

#include"Vec2.hpp"

class Animation {
    std::optional<sf::Sprite>              m_sprite;
    Vec2f                                  m_size; //texture widgth / frame count , texture height  (but this does not work for a texture of map which is very big)
    std::string                            m_name;
    int                                    m_frameCount;
    int                                    m_gameFrame;
    int                                    m_speed; //speed of the aniamtion (like every 10 frame a new anime frame to be shown)
    int                                    m_animeFrame; //what texture frame to show

    public:
    void update() {//TODO: only work for running of the character animation (according to the current textures the current asset and animation class might not work)
        // m_gameFrame++;
        // m_animeFrame=(m_gameFrame/m_speed) % m_frameCount;
        // m_sprite->setTextureRect(sf::IntRect({512,512*(m_animeFrame+1)},{m_size.x,m_size.y}));
    } 

    bool hasEnded() const {
        if((m_gameFrame/m_speed) / m_frameCount == 1) 
            return true;
        else return false;
    } 

    const std::string& getName() const {
        return m_name;
    }

    const Vec2f& getSize() const {
        return m_size;
    }

    std::optional<sf::Sprite>& getSprite() {
        return m_sprite;
    }
    
    Animation (const std::string& name, const int frameCount, const int animSpeed)
    :m_name(name), m_frameCount(frameCount), m_speed(animSpeed) {}
};