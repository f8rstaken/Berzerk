#pragma once

#include "Position.h"
#include "Renderer.h"
#include "SettingsManager.h"

class GameObject {

protected:
	Renderer renderer;
	Position position;

public:
	GameObject() : renderer(Renderer(SettingsManager::getInstance().getTextureSettings().defaultTexture)) {}
	GameObject(const char* texture) : renderer(Renderer(texture)) {}
	virtual ~GameObject() = default;

	Renderer& getRenderer() { 
		return renderer;
	}
	Position getPosition() {
		return this->position;
	}
	virtual void setPosition(float x, float y) { 
		position.x = x;
		position.y = y;
		renderer.setPosition(x, y);
	}
	virtual void render(sf::RenderWindow& window) {
        renderer.render(window);
    }
	
	virtual void update(float deltaTime) {

	}

};
