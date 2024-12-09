#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

class Renderer {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string texture_path;

public:
    Renderer(const std::string& texture_path)
        : texture_path(texture_path) {
        loadTexture();
    }
    ~Renderer() = default;

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    Renderer(Renderer&& other) noexcept = default;

    void loadTexture() {
        if (!texture.loadFromFile(texture_path)) {
            std::cout << "Failed to load texture: " << texture_path << std::endl;
        }
        
        sprite.setTexture(texture);
        const sf::Vector2f origin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        sprite.setOrigin(origin);
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

	void setTexture(const std::string& texture_path) {
		this->texture_path = texture_path;
		loadTexture();
	}

    const sf::Sprite& getSprite() const {
        return sprite;
    }

	const sf::FloatRect getBounds() const {
		return sprite.getGlobalBounds();
	}

    void render(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};
