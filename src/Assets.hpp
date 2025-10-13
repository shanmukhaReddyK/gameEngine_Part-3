#pragma once

#include"Animation.hpp"

#include<map>
#include<string>
#include<iostream>
#include<fstream>

#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>

class Assets {
    std::map<std::string, sf::Texture>                  m_textureMap;
    // std::map<std::string, sf::Sound>                    m_sounds;
    std::map<std::string, sf::Font>                     m_fontMap;
    std::map<std::string, Animation>                    m_animations;
    
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
                Vec2f start,size;
                fin >> name >> textureName>> frameCount >> animSpeed >> start.x >> start.y >> size.x >> size.y;
                addAnimation(name, textureName, frameCount, animSpeed, start,size);
            }
        }

    }

    //adding textures from config file
    void addTexture(const std::string& name, const std::string& path){
        try {
            sf::Texture tex{ path };
            // tex.setSmooth(true);  //set texture to smooth if needed
            m_textureMap.emplace(name, std::move(tex));
            std::cout << "Loaded Texture: " << path << "\n";
        }

        catch (const sf::Exception& e) {
            std::cerr << "Could not load texture file: " << path << " (" << e.what() << ")\n";
        }
    }

    // void addSound(const std::string& name, const std::string& path){
    //     //TODO: Implement sound
    //     std::cout<<"Audio still in progress\n";
    // }

    //adding fonts from config file
    void addFont(const std::string& name, const std::string& path){
        try {
            sf::Font fnt{ path };
            m_fontMap.emplace(name, std::move(fnt));
            std::cout << "Loaded Font:    " << path << "\n";
        }

        catch (const sf::Exception& e) {
            std::cerr << "Could not load font file: " << path << " (" << e.what() << ")\n";
        }
    }

    //adding animations from config file
    void addAnimation(const std::string& name, const std::string& textureName, const int frameCount, const int animSpeed, const Vec2f& start, const Vec2f& size) {
        auto it = m_animations.find(name);
        if (it != m_animations.end()) {
            std::cerr << "Warning: Animation '" << name << "' already exists, replacing it.\n";
            it->second = Animation(name, frameCount, animSpeed, start, size);
        } else {
            m_animations.emplace(name, Animation(name, frameCount, animSpeed, start, size));
        }

        m_animations[name].getSprite()=sf::Sprite(getTexture(textureName));
        m_animations[name].getSprite()->setOrigin({size.x/2,size.y/2});

        try {
            std::cout << "Loaded Animation:    " << name << "\n";
        }

        catch (const sf::Exception& e) {
            std::cerr << "Could not load Animation Sprite: " << name << " (" << e.what() << ")\n";
        }
    }

    
    const sf::Texture& getTexture(const std::string& name){ //TODO: use const if we not changing them like const sf::texture& and what if that name is not present if(m_textures.find(map)==m_textures.end())
        auto it = m_textureMap.find(name);
        assert(it != m_textureMap.end());
        return it->second;
    }

    // sf::Sound& getSound(const std::string& name){
    //     return m_sounds[name];
    // }

    const sf::Font& getFont(const std::string& name){
        auto it = m_fontMap.find(name);
        assert(it != m_fontMap.end());
        return it->second;
    }

    Animation& getAnimation(const std::string& name){
        auto it = m_animations.find(name);
        assert(it != m_animations.end());
        return it->second;
    }

    const std::map<std::string,Animation>& getAnimation() {
        return m_animations;
    }

};