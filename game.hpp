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
        sf::Font font;
        std::optional<sf::Text> gameOverText;

        bool gameInit();

        void processEvents();
        void getDirectionInput(const sf::Event& event);
        void handleClose(const sf::Event& event);
        bool foodEaten();
        void checkGameOver();
        bool endScreenInit();
        void showEndScreen();
        
        void update(float dt);
        
        void render(float dt);

        int score;
        bool isGameOver;

        Snake& snake;
        Food& food;

};