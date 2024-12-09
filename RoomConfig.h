#pragma once

#include <vector>
#include <tuple>
#include "Enemy.h"
#include "Wall.h"

struct RoomConfig {
    sf::Vector2f playerStartPosition;
    std::vector<std::tuple<float, float, int, int>> wallSpecs;
    std::vector<sf::Vector2f> enemyPositions;
};
