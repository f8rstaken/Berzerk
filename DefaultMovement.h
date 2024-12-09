#pragma once

#include "MovementBehaviour.h"
#include "MovementState.h"

class DefaultMovement : public MovementBehaviour {

public:
	DefaultMovement(float speed) : MovementBehaviour(speed) {}

	void move(GameObject& GameObject, Position::Direction dir, float deltaTime) {
		if (dir == Position::Direction::UNKWN) {
			return;
		}
		float distance = speed * deltaTime;
		Position updatedPosition = GameObject.getPosition().updatePosition(dir, distance);
		GameObject.setPosition(updatedPosition.x, updatedPosition.y);
	}

	void update(GameObject& gameObject, float deltaTime) override {
		for (const auto& [dir, isMoving] : movementState.getStates()) {
            if (isMoving) {
                move(gameObject, dir, deltaTime);
            }
        }
	}

	void setMovingState(Position::Direction dir, bool isMoving) override {
		movementState.setState(dir, isMoving);
	}

};
