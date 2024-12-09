#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "InputControl.h"
#include "MovementBehaviour.h"
#include "Position.h"
#include "SettingsManager.h"
#include "EventSystem.h"
#include "ProjectileEvent.h"
#include "ScoreSystem.h"
#include <iostream>

class Player : public GameObject {

private:
	InputControl inputControls;
	std::unique_ptr<MovementBehaviour> movementBehaviour;
	ScoreSystem scoreSystem;

public:
	Player(std::unique_ptr<MovementBehaviour> movementBehaviour)
	: GameObject(SettingsManager::getInstance().getTextureSettings().player), movementBehaviour(std::move(movementBehaviour)) {
		configureInput();
	}
	~Player() = default;
	
	InputControl* GetInputControls() {
		return &this->inputControls;
	}

	std::unique_ptr<MovementBehaviour>& GetMovementBehaviour() {
		return movementBehaviour; 
	}

	ScoreSystem& GetScoreSystem() {
		return scoreSystem;
	}

	void update(float deltaTime) override {
		if (movementBehaviour) {
			movementBehaviour->update(*this, deltaTime);
		}
	}

	void shoot() {
		ProjectileEvent data = {this, this->GetMovementBehaviour()->getMovementState().getLastDirection()};
		EventSystem::getInstance()->publish(EventType::SPAWN_PROJECTILE, data);
	}

	void configureInput() {
		KeybindSettings keybinds = SettingsManager::getInstance().getKeybindSettings();

		inputControls.SetMapping(keybinds.moveUp, [this]() { movementBehaviour->setMovingState(Position::Direction::UP, true); }, sf::Event::KeyPressed);
		inputControls.SetMapping(keybinds.moveLeft, [this]() { movementBehaviour->setMovingState(Position::Direction::LEFT, true); }, sf::Event::KeyPressed);
		inputControls.SetMapping(keybinds.moveDown, [this]() { movementBehaviour->setMovingState(Position::Direction::DOWN, true); }, sf::Event::KeyPressed);
		inputControls.SetMapping(keybinds.moveRight, [this]() { movementBehaviour->setMovingState(Position::Direction::RIGHT, true); }, sf::Event::KeyPressed);

		inputControls.SetMapping(keybinds.moveUp, [this]() { movementBehaviour->setMovingState(Position::Direction::UP, false); }, sf::Event::KeyReleased);
		inputControls.SetMapping(keybinds.moveLeft, [this]() { movementBehaviour->setMovingState(Position::Direction::LEFT, false); }, sf::Event::KeyReleased);
		inputControls.SetMapping(keybinds.moveDown, [this]() { movementBehaviour->setMovingState(Position::Direction::DOWN, false); }, sf::Event::KeyReleased);
		inputControls.SetMapping(keybinds.moveRight, [this]() { movementBehaviour->setMovingState(Position::Direction::RIGHT, false); }, sf::Event::KeyReleased);
		inputControls.SetMapping(keybinds.shoot, [this]() {this->shoot(); }, sf::Event::KeyReleased);
	}

};