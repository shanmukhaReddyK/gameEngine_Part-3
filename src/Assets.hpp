#pragma once

#include"Animation.hpp"

#include<map>
#include<string>
#include<iostream>

#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>

class Assets {
    std::map<std::string, sf::Texture>       m_textures;
    std::map<std::string, sf::Sound>         m_sounds;
    std::map<std::string, sf::Font>          m_fonts;
    //TODO: declare below when animations is done
    //std::map<std::string,Animations>        m_animations
    
    public:
    void loadFromFile(const std::string& assetConfig) {

    }

    void addTexture(const std::string& name, const std::string& path){

        if(m_textures.find(name)==m_textures.end())
            m_textures[name]=sf::Texture();
        
        if(!m_textures[name].loadFromFile(path)) {
            std::cout<<"unable to open " << name << "file\n";
        }
    }

    void addSound(const std::string& name, const std::string& path){
        //TODO: Implement sound
        std::cout<<"Audio still in progress\n";
    }

    void addFont(const std::string& name, const std::string& path){
        if(m_fonts.find(name)==m_fonts.end())
            m_fonts[name]=sf::Font();
        
        if(!m_fonts[name].openFromFile(path)) {
            std::cout<<"unable to open " << name << "file\n";
        }
    }

    //TODO: declare below when animations is done
    //void addAnimation(const std::string& name, Animation&){}

    sf::Texture& getTexture(const std::string& name){ //TODO: use const if we not changing them like const sf::texture& and what if that name is not present if(m_textures.find(map)==m_textures.end())
        return m_textures[name];
    }

    sf::Sound& getSound(const std::string& name){
        return m_sounds[name];
    }

    sf::Font& getFont(const std::string& name){
        return m_fonts[name];
    }

};