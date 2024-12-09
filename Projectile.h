#pragma once
#include "GameObject.h"
#include "MovementBehaviour.h"
#include "SettingsManager.h"

class Projectile : public GameObject {
private:
	std::unique_ptr<MovementBehaviour> movementBehaviour;

public:
	Projectile(std::unique_ptr<MovementBehaviour> movementBehaviour)
		: GameObject(SettingsManager::getInstance().getTextureSettings().bullet), movementBehaviour(std::move(movementBehaviour)) {}
	Projectile();

	void update(float deltaTime) override {
		if (movementBehaviour) {
			movementBehaviour->update(*this, deltaTime);
		}
	}
		
};
