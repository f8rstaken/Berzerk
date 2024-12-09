#pragma once 

namespace Settings {
	namespace Window {
		constexpr int Width = 800;
		constexpr int Height = 600;
	}

	namespace Texture {
		constexpr const char* Player = "player.png";
		constexpr const char* Enemy = "enemy.png";
		constexpr const char* Bullet = "bullet.png";
		constexpr const char* Wall = "wall.png";
		constexpr const char* Default = "missing.png";
	}

	namespace Keybinds {
		constexpr sf::Keyboard::Key MoveUp = sf::Keyboard::W;
		constexpr sf::Keyboard::Key MoveDown = sf::Keyboard::S;
		constexpr sf::Keyboard::Key MoveLeft = sf::Keyboard::A;
		constexpr sf::Keyboard::Key MoveRight = sf::Keyboard::D;
		constexpr sf::Keyboard::Key Shoot = sf::Keyboard::Space;
	}

}