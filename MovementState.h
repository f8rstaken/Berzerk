#pragma once

#include "Position.h"
#include <unordered_map>

class MovementState {
private:
	std::unordered_map<Position::Direction, bool> movementStates;
	Position::Direction lastDirection = Position::Direction::UNKWN;

public:
	MovementState() {
		movementStates[Position::Direction::UP] = false;
		movementStates[Position::Direction::RIGHT] = false;
		movementStates[Position::Direction::DOWN] = false;
		movementStates[Position::Direction::LEFT] = false;
	}

	const std::unordered_map<Position::Direction, bool>& getStates() const {
		return movementStates;
	}

	void setState(Position::Direction dir, bool state) {
		movementStates[dir] = state;
		if (dir != Position::Direction::UNKWN && state) {
			lastDirection = dir;
		}
	}

	Position::Direction getLastDirection() const {
		return lastDirection;
	}

	void clear() {
		for (auto& state : movementStates) {
			state.second = false;
		}
	}

	bool isMoving(Position::Direction dir) const {
		auto it = movementStates.find(dir);
		return it != movementStates.end() && it->second;	
	}

	Position::Direction getActiveDirection() const {
		for (const auto& [dir, state] : movementStates) {
			if (state) {
				return dir;
			}
        }
		return Position::Direction::UNKWN;
	}

};
