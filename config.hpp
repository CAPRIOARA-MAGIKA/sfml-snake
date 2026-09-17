#pragma once
#include <SFML\Graphics.hpp>

namespace GameConfig{
    constexpr unsigned int WINDOW_RESOLUTION_X = 800;
    constexpr unsigned int WINDOW_RESOLUTION_Y = 600;

    constexpr float CELL_SIZE = 32.0f;
    constexpr float OFFSET_X = 80.0f;
    constexpr float OFFSET_Y = 60.0f;
    constexpr unsigned int NUMBER_CELLS_X = 20;
    constexpr unsigned int NUMBER_CELLS_Y = 15;

    constexpr float SNAKE_SPEED = 256.0f;
    constexpr int STARTING_SEGMENTS = 3;

    constexpr unsigned int SNAKE_START_CELL_X = 9;
    constexpr unsigned int SNAKE_START_CELL_Y = 7;
    constexpr float SNAKE_START_X = OFFSET_X + (SNAKE_START_CELL_X * CELL_SIZE) + (CELL_SIZE / 2.0f);
    constexpr float SNAKE_START_Y = OFFSET_Y + (SNAKE_START_CELL_Y * CELL_SIZE) + (CELL_SIZE / 2.0f);
}