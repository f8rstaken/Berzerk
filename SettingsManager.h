#pragma once

#include "WindowSettings.h"
#include "TextureSettings.h"
#include "KeyboardSettings.h"
#include "GameSettings.h"

class SettingsManager {
private:
    WindowSettings windowSettings;
    TextureSettings textureSettings;
    KeybindSettings keybindSettings;
	GameSettings gameSettings;

    SettingsManager() {
        windowSettings = { 800, 600 };
        textureSettings = { "player.png", "enemy.png", "bullet.png", "wall.png", "missing.png" };
        keybindSettings = { sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::Space };
        gameSettings = { 300.0f, "minecraft.otf"};
    }

public:
	static SettingsManager& getInstance() {
		static SettingsManager instance;
		return instance;
	}

    WindowSettings getWindowSettings() const { return windowSettings; }
    TextureSettings getTextureSettings() const { return textureSettings; }
    KeybindSettings getKeybindSettings() const { return keybindSettings; }
	GameSettings getGameSettings() const { return gameSettings; }
};
