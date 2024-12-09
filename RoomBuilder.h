#pragma once

#include <vector>
#include <memory>
#include "Wall.h"

class RoomBuilder {

public:
	std::vector<std::unique_ptr<Wall>> generateWalls(const std::vector<std::tuple<float, float, int, int>>& wallSpecs, float spacing = 16) {
		std::vector<std::unique_ptr<Wall>> walls;

		for (const auto& spec : wallSpecs) {
			float startX = std::get<0>(spec);
			float startY = std::get<1>(spec);
			int width = std::get<2>(spec);
			int length = std::get<3>(spec);

			for (int row = 0; row < length; ++row) {
				for (int col = 0; col < width; ++col) {
					auto wall = std::make_unique<Wall>();
					wall->setPosition(startX + col * spacing, startY + row * spacing);
					walls.push_back(std::move(wall));
				}
			}
		}

		return walls;
    }

};
