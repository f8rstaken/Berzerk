#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class TextDrawer {

public:
	static void drawText(sf::RenderWindow& window, sf::Vector2f position, std::string text, std::string fontName, sf::Color textColor) {
		sf::Font font;
		if (!font.loadFromFile(fontName)) {
			std::cout << "Failed to load font" << std::endl;
			return;
		}

		sf::Text textObj;
		textObj.setFont(font);
		textObj.setString(text);
		textObj.setCharacterSize(24);
		textObj.setFillColor(textColor);
		textObj.setPosition(position);
		window.draw(textObj);
	}

};
