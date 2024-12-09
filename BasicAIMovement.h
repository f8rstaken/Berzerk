#pragma once

#include "MovementBehaviour.h"
#include "MovementState.h"
#include <iostream>
#include <random>
#include <chrono>

class BasicAIMovement : public MovementBehaviour {

private:
	float timeAccumulatorS = 0.0f; 
    float changeIntervalS = 1.0f;
	std::default_random_engine rng;
	std::uniform_int_distribution<int> directionDist;

	void changeRandomDirection() {
		movementState.clear();
		int direction = directionDist(rng);
		Position::Direction newDirection = static_cast<Position::Direction>(direction);
		movementState.setState(newDirection, true);
	}

public:
	BasicAIMovement(float speed)
		: MovementBehaviour(speed),
		rng(std::chrono::system_clock::now().time_since_epoch().count()),
		directionDist(0, 4) {}

	void update(GameObject& GameObject, float deltaTime) override {
		timeAccumulatorS += deltaTime;

        if (timeAccumulatorS >= changeIntervalS) {
            timeAccumulatorS = 0.0f;
			changeRandomDirection();
        }
		move(GameObject, movementState.getActiveDirection(), deltaTime);
	}

	void move(GameObject& GameObject, Position::Direction dir, float deltaTime) {
		if (dir == Position::Direction::UNKWN) {
			return;
		}
		float distance = speed * deltaTime;
		Position updatedPosition = GameObject.getPosition().updatePosition(dir, distance);
		GameObject.setPosition(updatedPosition.x, updatedPosition.y);
	}

	void setMovingState(Position::Direction dir, bool isMoving) override {
		movementState.setState(dir, isMoving);
	}

};
