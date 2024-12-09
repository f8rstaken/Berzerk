#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class CollisionChecker {
public:
    static bool checkCollision(GameObject& GameObject1, GameObject& GameObject2) {
		sf::FloatRect box1 = GameObject1.getRenderer().getBounds();
        sf::FloatRect box2 = GameObject2.getRenderer().getBounds();
        
        return box1.intersects(box2);
    }

	static bool checkLevelBounds(GameObject& GameObject, sf::Vector2f size) {
		sf::FloatRect box = GameObject.getRenderer().getBounds();
		sf::FloatRect levelBounds(box.width, box.height, size.x - box.width * 2, size.y - box.height * 2);

		return !levelBounds.intersects(box);
	}

};
