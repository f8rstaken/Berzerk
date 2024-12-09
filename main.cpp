#include "Game.h"
#include "CollisionTests.h"

void runGame() {
	Game game;
	game.start();
}

void runTests() {
	CollisionTests ct;
	ct.runAll();
}

int main() {

	runGame();

    return 0;
}   
