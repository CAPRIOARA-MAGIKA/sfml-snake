#pragma once
#include "config.hpp"
#include "snake.hpp"
#include "food.hpp"
#include <SFML/Graphics.hpp>
#include <optional>

class Game{
    public:
        Game(Snake& s, Food& f);

        bool init();
        void run();

    private:
        sf::RenderWindow window;
        sf::Clock gameClock;
        sf::Texture bgTexture;
        std::optional<sf::Sprite> bgSprite;

        bool gameInit();

        void processEvents();
        void getDirectionInput(const sf::Event& event);
        void handleClose(const sf::Event& event);
        bool foodEaten();
        void checkGameOver();
        
        void update(float dt);
        
        void render(float dt);

        int score;
        bool isGameOver;

        Snake& snake;
        Food& food;

};