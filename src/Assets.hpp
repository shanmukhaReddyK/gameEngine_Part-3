#pragma once

#include"Animation.hpp"

#include<map>
#include<string>
#include<iostream>
#include<fstream>

#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>

class Assets {
    std::map<std::string, sf::Texture>                  m_textures;
    // std::map<std::string, sf::Sound>                    m_sounds;
    std::map<std::string, sf::Font>                     m_fonts;
    std::map<std::string, std::shared_ptr<Animation>>   m_animations;
    
    public:
    void loadFromfile(const std::string& assetConfig) {
        std::ifstream fin(assetConfig);
    
        if(!fin.is_open()) {
            std::cerr<<"Error opening file "<< assetConfig <<"\n";
        }

        std::string word;

        while(fin >> word) {
            if(word == "Texture") {
                std::string name,path;
                fin >> name >> path;
                addTexture(name,path);
            }

            if(word == "Font") {
                std::string name,path;
                fin >> name >> path;
                addFont(name,path);
            }

            // if(word == "Sound") {
            //     std::string name,path;
            //     fin >> name >> path;
            //     addTexture(name,path);
            // }

            if(word == "Animation") {
                std::string name,textureName;
                int frameCount,animSpeed;
                fin >> name >> textureName>> frameCount >> animSpeed;
                addAnimation(name, textureName, frameCount, animSpeed);
            }
        }

    }

    void addTexture(const std::string& name, const std::string& path){

        if(m_textures.find(name)==m_textures.end())
            m_textures[name]=sf::Texture();
        
        if(!m_textures[name].loadFromFile(path)) {
            std::cout<<"unable to open " << name << "file\n";
        }
    }

    // void addSound(const std::string& name, const std::string& path){
    //     //TODO: Implement sound
    //     std::cout<<"Audio still in progress\n";
    // }

    void addFont(const std::string& name, const std::string& path){
        if(m_fonts.find(name)==m_fonts.end())
            m_fonts[name]=sf::Font();
        
        if(!m_fonts[name].openFromFile(path)) {
            std::cout<<"unable to open " << name << "file\n";
        }
    }


    void addAnimation(const std::string& name, const std::string& textureName, const int frameCount, const int animSpeed) {
        if(m_animations.find(name)==m_animations.end()) {
            m_animations[name] = std::make_shared<Animation>(name,frameCount,animSpeed);
        }

        m_animations[name]->getSprite()=sf::Sprite(getTexture(textureName));
    }

    sf::Texture& getTexture(const std::string& name){ //TODO: use const if we not changing them like const sf::texture& and what if that name is not present if(m_textures.find(map)==m_textures.end())
        return m_textures[name];
    }

    // sf::Sound& getSound(const std::string& name){
    //     return m_sounds[name];
    // }

    sf::Font& getFont(const std::string& name){
        return m_fonts[name];
    }

    std::shared_ptr<Animation> getAnimation(const std::string& name){
        return m_animations[name];
    }

};