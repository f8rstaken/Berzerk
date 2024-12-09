#pragma once

#include "Renderer.h"
#include "MovementBehaviour.h"
#include "SettingsManager.h"

class Enemy : public GameObject {
private:
	std::unique_ptr<MovementBehaviour> movementBehaviour;

public:
	Enemy(std::unique_ptr<MovementBehaviour> movementBehaviour)
	: GameObject(SettingsManager::getInstance().getTextureSettings().enemy), movementBehaviour(std::move(movementBehaviour)) {}
	
	void update(float deltaTime) override {
		if (movementBehaviour) {
			movementBehaviour->update(*this, deltaTime);
		}
	}


};
