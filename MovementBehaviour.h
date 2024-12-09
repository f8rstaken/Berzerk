#pragma once

#include "MovementState.h"
#include "GameObject.h"
#include "Position.h"

class MovementBehaviour {
protected:
    float speed;
    MovementState movementState;

public:
    MovementBehaviour(float speed) : speed(speed) {}
    virtual ~MovementBehaviour() = default;

    virtual void update(GameObject& gameObject, float deltaTime) = 0;
    virtual void setMovingState(Position::Direction dir, bool isMoving) = 0;

    void setSpeed(float newSpeed) { speed = newSpeed; }
    float getSpeed() const { return speed; }
    MovementState& getMovementState() { return movementState; }
};