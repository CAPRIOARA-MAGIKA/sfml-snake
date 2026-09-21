#include "snake.hpp"

Snake::Snake() 
    : direction(Direction::UP),
      nextDirection(Direction::UP), 
      directionMoved(0.0f),
      segment(GameConfig::STARTING_SEGMENTS),
      isSnakeDead(false)
{      

}

bool Snake::init(){
    if(!headTexture.loadFromFile("snake_head.png")){
        return false;
    }
    if(!bodyTexture.loadFromFile("snake_body.png")){
        return false;
    }

    headSprite.emplace(headTexture);
    bodySprite.emplace(bodyTexture);
    
    headSprite->setOrigin({GameConfig::CELL_SIZE/2, GameConfig::CELL_SIZE/2});
    bodySprite->setOrigin({GameConfig::CELL_SIZE/2, GameConfig::CELL_SIZE/2});
    headSprite->setPosition({GameConfig::SNAKE_START_X, GameConfig::SNAKE_START_Y});

    return true;
}

void Snake::setDirection(Direction newDirection){
    if(newDirection == Direction::UP && nextDirection == Direction::DOWN){
        return;
    }
    if(newDirection == Direction::DOWN && nextDirection == Direction::UP){
        return;
    }
    if(newDirection == Direction::LEFT && nextDirection == Direction::RIGHT){
        return;
    }
    if(newDirection == Direction::RIGHT && nextDirection == Direction::LEFT){
        return;
    }
    nextDirection = newDirection;
}

void Snake::moveHead(float dt){
    switch(direction){
        case Direction::UP:
            headSprite->move({0.0f, -GameConfig::SNAKE_SPEED*dt});
            headSprite->setRotation(sf::degrees(0));
            break;
        case Direction::DOWN:
            headSprite->move({0.0f, GameConfig::SNAKE_SPEED*dt});
            headSprite->setRotation(sf::degrees(180));
            break;
        case Direction::LEFT:
            headSprite->move({-GameConfig::SNAKE_SPEED*dt, 0.0f});
            headSprite->setRotation(sf::degrees(270));
            break;
        case Direction::RIGHT:
            headSprite->move({GameConfig::SNAKE_SPEED*dt, 0.0f});
            headSprite->setRotation(sf::degrees(90));
            break;
    }
}

void Snake::grow(){
    segment++;
}

void Snake::update(float dt){
    moveHead(dt);
    checkForCollisionWall();
    checkForCollisionBody(dt);
    
    TransformSegment headState;
    headState.position = headSprite->getPosition();
    headState.rotation = headSprite->getRotation();
    headPastPos.push_front(headState);

    directionMoved = directionMoved + GameConfig::SNAKE_SPEED*dt;
    if(directionMoved >= GameConfig::CELL_SIZE){
        direction = nextDirection;
        directionMoved = directionMoved - GameConfig::CELL_SIZE;

        sf::Vector2f currentPosition = headSprite->getPosition();
        headSprite->setPosition({
            GameConfig::OFFSET_X + std::round((currentPosition.x - GameConfig::OFFSET_X - GameConfig::CELL_SIZE / 2.0f) / GameConfig::CELL_SIZE) * GameConfig::CELL_SIZE + GameConfig::CELL_SIZE / 2.0f,
            GameConfig::OFFSET_Y + std::round((currentPosition.y - GameConfig::OFFSET_Y - GameConfig::CELL_SIZE / 2.0f) / GameConfig::CELL_SIZE) * GameConfig::CELL_SIZE + GameConfig::CELL_SIZE / 2.0f
        });
    }

    unsigned int maxHistory = (segment + 2) * (GameConfig::CELL_SIZE / (GameConfig::SNAKE_SPEED * dt + 0.001f));
    if(maxHistory < headPastPos.size()){
        headPastPos.pop_back();
    }
}

void Snake::checkForCollisionWall(){
    float headXPos = getHeadPos().x;
    float headYPos = getHeadPos().y;
    if(headXPos < GameConfig::OFFSET_X ||
       headXPos > GameConfig::OFFSET_X + GameConfig::NUMBER_CELLS_X * GameConfig::CELL_SIZE ||
       headYPos < GameConfig::OFFSET_Y ||
       headYPos > GameConfig::OFFSET_Y + GameConfig::NUMBER_CELLS_Y * GameConfig::CELL_SIZE
    ) {
        isSnakeDead = true;
    }
}

void Snake::checkForCollisionBody(float dt){
    int minSegmente = 4;

    for(int i = minSegmente; i < segment; ++i){
        TransformSegment bodyState = getPosAndRot(i, dt);
        sf::Vector2f diff = headSprite->getPosition() - bodyState.position;
        float diffSquare = diff.x * diff.x + diff.y * diff.y;

        float collisionRadius = GameConfig::CELL_SIZE * 0.4f;
        if(diffSquare < collisionRadius * collisionRadius){
            isSnakeDead = true;
            return;
        }
    }
}

TransformSegment Snake::getPosAndRot(int segmentIndex, float dt){
    float distancePerFrame = GameConfig::SNAKE_SPEED * dt;
    if(distancePerFrame <= 0.0f){
        return headPastPos.front();
    }

    int framesPerCell = static_cast<int>(GameConfig::CELL_SIZE / distancePerFrame);
    unsigned int historyIndex = framesPerCell * segmentIndex;

    if(historyIndex >= headPastPos.size()){
        return headPastPos.back();
    }

    return headPastPos[historyIndex];
}

void Snake::render(sf::RenderWindow& window, float dt){
    if(segment > 0 && !headPastPos.empty()){
        for(int i = segment; i >= 1; --i){
            TransformSegment bodyState = getPosAndRot(i, dt);
            bodySprite->setPosition(bodyState.position);
            bodySprite->setRotation(bodyState.rotation);
            window.draw(*bodySprite);
        }
    }
    window.draw(*headSprite);
}


//Ca sa faci Colision cu snake trb sa verifici daca un trunchi intra in cap, nu daca capul intra in trunchi.