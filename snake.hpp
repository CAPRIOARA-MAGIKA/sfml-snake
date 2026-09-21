#pragma once
#include "config.hpp"
#include <SFML/Graphics.hpp>
#include <optional>
#include <deque>

struct TransformSegment{
    sf::Vector2f position;
    sf::Angle rotation;
};

class Snake{
    public:
        enum class Direction{
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
    
        Snake();
        bool init();

        sf::Vector2f getHeadPos() const {return headSprite->getPosition();}

        void setDirection(Direction dir);
        void grow();
        bool isSnakeDead;

        void update(float dt);
        void render(sf::RenderWindow& window, float dt);

    private:

        sf::Texture headTexture;
        sf::Texture bodyTexture;
        std::optional<sf::Sprite> headSprite;
        std::optional<sf::Sprite> bodySprite;
        std::deque<TransformSegment> headPastPos;

        float directionMoved;
        Direction direction;
        Direction nextDirection;
        int segment;

        void moveHead(float dt);
        TransformSegment getPosAndRot(int segmentIndex, float dt);
        void checkForCollisionWall();
        void checkForCollisionBody(float dt);
};