#pragma once

class Position {

public:
	enum class Direction {
		UNKWN,
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	float x, y;

	Position() = default;
	
	Position(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Position updatePosition(Direction dir, float amount) {
		switch (dir) {
			case Direction::UP:
				y -= amount;
				break;
			case Direction::RIGHT:
				x += amount;
				break;
			case Direction::DOWN:
				y += amount;
				break;
			case Direction::LEFT:
				x -= amount;
				break;
		}
		return *this;
	}


};