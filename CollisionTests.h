#pragma once

#include "CollisionChecker.h" 
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include <cassert>

class CollisionTests {
private:
	void testCollisionCheckerCollide() {
		GameObject gameObject1;
		GameObject gameObject2; 

		gameObject1.setPosition(0, 0);
		gameObject2.setPosition(0, 0);

		assert(CollisionChecker::checkCollision(gameObject1, gameObject2));
	}

	void testCollisionCheckerNotCollide() {
		GameObject gameObject1;
		GameObject gameObject2;

		gameObject1.setPosition(0, 0);
		gameObject2.setPosition(100, 100);

		assert(!CollisionChecker::checkCollision(gameObject1, gameObject2));
	}

	void testCollisionCheckerLevelBoundsCollide() {
		GameObject gameObject;
		sf::Vector2f size(100, 100);

		gameObject.setPosition(0, 0);

		assert(CollisionChecker::checkLevelBounds(gameObject, size));
	}

	void testCollisionCheckerLevelBoundsNotCollide() {
		GameObject gameObject;
		sf::Vector2f size(100, 100);

		gameObject.setPosition(50, 50);

		assert(!CollisionChecker::checkLevelBounds(gameObject, size));
	}

public:
	void runAll() {
		testCollisionCheckerCollide();
		testCollisionCheckerNotCollide();
		testCollisionCheckerLevelBoundsCollide();
		testCollisionCheckerLevelBoundsNotCollide();
	}

};

