#pragma once

#include<string>
#include<SFML/Graphics.hpp>
#include<iostream>
#include"Vec2.hpp"

class Animation {
    std::optional<sf::Sprite>              m_sprite;
    Vec2f                                  m_size; //texture widgth / frame count , texture height  (but this does not work for a texture of map which is very big)
    Vec2f                                  m_startPoint;
    std::string                            m_name;
    int                                    m_frameCount=0;
    int                                    m_gameFrame=0;
    int                                    m_speed; //speed of the aniamtion (like every 10 frame a new anime frame to be shown)
    int                                    m_animeFrame=0; //what texture frame to show

    public:

    Animation() = default;

    Animation (const std::string& name, const int frameCount, const int animSpeed,const Vec2f& start, const Vec2f& size)
    :m_name(name), m_frameCount(frameCount), m_speed(animSpeed), m_startPoint(start), m_size(size) {}



    void update() {//TODO: only work for running of the character animation (according to the current textures the current asset and animation class might not work)
        m_gameFrame++;
        if(m_frameCount>1) {
        m_animeFrame=(m_gameFrame/m_speed) % m_frameCount;
        }
        // if(m_name=="SamuraiRun") {
        // std::cout<<"anime frame:"<<m_animeFrame<<"\n";
        // std::cout<<"speed:"<<m_speed<<"\n";
        // std::cout<<"game frame:"<<m_gameFrame<<"\n";
        // std::cout<<"X "<<(int)(m_startPoint.x+m_size.x*(m_animeFrame));
        // }
        m_sprite->setTextureRect(sf::IntRect({(int)(m_startPoint.x+m_size.x*(m_animeFrame)),(int)m_startPoint.y},{(int)m_size.x,(int)m_size.y}));
    } 

    bool hasEnded() const {
        if((m_gameFrame/m_speed) >= m_frameCount) 
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
};