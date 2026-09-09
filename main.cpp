#include "game.hpp"
#include "snake.hpp"
#include "food.hpp"

int main(){
    Snake snake;
    Food food;
    Game game(snake, food);

    if(!game.init()){
        return -1;
    }

    game.run();
    return 0;
}