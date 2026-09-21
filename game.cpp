#include "game.hpp"
#include <iostream>

Game::Game(Snake& s, Food& f) 
    : window(sf::VideoMode({GameConfig::WINDOW_RESOLUTION_X, GameConfig::WINDOW_RESOLUTION_Y}), "SNAKE"),
      score(0), 
      isGameOver(false), 
      snake(s), 
      food(f)
{
    
}

bool Game::init(){
    if(!snake.init()){
        std::cerr << "Failed to initialize snake textures!\n";
        return false;
    }
    if(!food.init()){
        std::cerr << "Failed to initialize food texture!\n";
        return false;
    }
    if(!gameInit()){
        std::cerr << "Failed to initialize background texture!\n";
        return false;
    }
    return true;
}

bool Game::gameInit(){
    if(!bgTexture.loadFromFile("snake_background.png")){
        return false;
    }
    
    bgSprite.emplace(bgTexture);
    
    return true;
}

void Game::getDirectionInput(const sf::Event& event){
    if(const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()){
        if(keyPressed->code == sf::Keyboard::Key::W || keyPressed->code == sf::Keyboard::Key::Up){
            snake.setDirection(Snake::Direction::UP);
        }
        else if(keyPressed->code == sf::Keyboard::Key::S || keyPressed->code == sf::Keyboard::Key::Down){
            snake.setDirection(Snake::Direction::DOWN);
        }
        else if(keyPressed->code == sf::Keyboard::Key::A || keyPressed->code == sf::Keyboard::Key::Left){
            snake.setDirection(Snake::Direction::LEFT);
        }
        else if(keyPressed->code == sf::Keyboard::Key::D || keyPressed->code == sf::Keyboard::Key::Right){
            snake.setDirection(Snake::Direction::RIGHT);
        }
    }
}

void Game::handleClose(const sf::Event& event){
    if(event.is<sf::Event::Closed>()){
            window.close();
    }
}

void Game::run(){
    while(window.isOpen()){

        sf::Time dtTime = gameClock.restart();
        float dt = dtTime.asSeconds();

        processEvents();

        update(dt);

        if(isGameOver){
            break;
        }

        render(dt);

    }
}

void Game::render(float dt){
    window.clear();
    window.draw(*bgSprite);
    snake.render(window, dt);
    food.render(window);
    window.display();
}

bool Game::foodEaten(){
    if(snake.getHeadPos() == food.getPos()){
        score++;
        return true;
    }
    return false;
}

void Game::checkGameOver(){
    if(snake.isSnakeDead){
        isGameOver = true;
    }
}

void Game::update(float dt){
    checkGameOver();
    snake.update(dt);
    if(foodEaten()){
        food.update();
        snake.grow();
    }
}

void Game::processEvents(){
    while(const std::optional<sf::Event> event = window.pollEvent()){
        handleClose(*event);
        
        getDirectionInput(*event);
    }
}

/*
 FACI CA MANCAREA SA FIE PLASATA RANDOM PE UNA DINTRE PATRATELE (faci total lungime pixel / cate patratele is si dupa scazi jumate de patratica la ambele coordonate)
 FACI CA SNAKE SA SE MISTE CONTINUU DAR SA PRIMEASCA INPUT PE UN CLOCK (sau faci ca miscatul sa se intample de mai multe ori decat check de directie)
 LA SNAKE FACI CA ULTIMA BUCATA DINAINTE SA SE TELEPORTEZE IN POZITIA LA URMATOAREA BUCATA




*/