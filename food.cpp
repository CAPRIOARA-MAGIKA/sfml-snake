#include "food.hpp"
#include <random>

Food::Food() 
    : rng(std::random_device{}())
{     
    
};

bool Food::init(){
    if(!foodTexture.loadFromFile("snake_food.png")){
        return false;
    }

    foodSprite.emplace(foodTexture);
    foodSprite->setOrigin({GameConfig::CELL_SIZE/2, GameConfig::CELL_SIZE/2});

    spawnInRandomPos();

    return true;
}

void Food::spawnInRandomPos(){
    unsigned int CellX, CellY;
    CellX = std::uniform_int_distribution<unsigned int>(0, GameConfig::NUMBER_CELLS_X - 1)(rng);
    CellY = std::uniform_int_distribution<unsigned int>(0, GameConfig::NUMBER_CELLS_Y - 1)(rng);

    foodSprite->setPosition({
        GameConfig::OFFSET_X + GameConfig::CELL_SIZE * CellX + GameConfig::CELL_SIZE/2,
        GameConfig::OFFSET_Y + GameConfig::CELL_SIZE * CellY + GameConfig::CELL_SIZE/2
    });
}

void Food::update(){
    spawnInRandomPos();
}

void Food::render(sf::RenderWindow& window){
    window.draw(*foodSprite);
}