#pragma once
#include "config.hpp"
#include <SFML/Graphics.hpp>
#include <optional>
#include <random>

class Food{
    private:
        sf::Texture foodTexture;
        std::optional<sf::Sprite> foodSprite;
        std::mt19937 rng;

        void spawnInRandomPos();
    public:
        Food();
        
        sf::Vector2f getPos() const {return foodSprite->getPosition();}
        
        bool init();

        void update();
        void render(sf::RenderWindow& window);
};