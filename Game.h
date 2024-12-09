#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Player.h"
#include "Wall.h"
#include "Enemy.h"
#include "DefaultMovement.h"
#include "CollisionChecker.h"
#include "TextDrawer.h"
#include "Rooms.h"
#include "RandomGenerator.h"
#include "PlayerKillEvent.h"

enum class GameState {
	RUNNING,
	GAME_OVER,
    GAME_WON
};

class Game {
private:
	Player player;
	Level currentLevel;
	sf::RenderWindow window;
	int score = 0;
	GameState state = GameState::RUNNING;
	std::vector<RoomConfig> enabledRooms = { Rooms::Room1, Rooms::Room2 };

    void resetGame(bool resetScore = true) {
        if (resetScore) {
            score = 0;
        }   
        player.GetMovementBehaviour()->getMovementState().clear();
           
		currentLevel = Level();
        currentLevel.setPlayer(&player);
        currentLevel.loadLevel(enabledRooms[RandomGenerator::getRandomInt(0, enabledRooms.size() - 1)]);
        state = GameState::RUNNING;
    }

	void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::R) {
                        resetGame();
                    } else if (state == GameState::GAME_WON && event.key.code == sf::Keyboard::Return) {
                        resetGame(true);
                    } else if (state == GameState::RUNNING) {
                        player.GetInputControls()->ExecuteKey(event.key.code, event.type);
                    }
                    break;
            }
        }
    }

    void renderGameOverScreen() {
        sf::Font font;
        font.loadFromFile(SettingsManager::getInstance().getGameSettings().defaultFont);
        sf::Text gameOverText("Game Over! Press R to Restart", font, 24);
        gameOverText.setFillColor(sf::Color::Red);
		WindowSettings windowSettings = SettingsManager::getInstance().getWindowSettings();
        gameOverText.setPosition(windowSettings.height / 4, windowSettings.width / 4);
        window.draw(gameOverText);
    }
    
	void renderGameWonScreen() {
		sf::Font font;
        font.loadFromFile(SettingsManager::getInstance().getGameSettings().defaultFont);
		sf::Text gameOverText("You won! Press Enter to continue", font, 24);
		gameOverText.setFillColor(sf::Color::Green);
		WindowSettings windowSettings = SettingsManager::getInstance().getWindowSettings();
        gameOverText.setPosition(windowSettings.height / 4, windowSettings.width / 4);
		window.draw(gameOverText);
	}

    void subscribeToEvents() {
        EventSystem::getInstance()->subscribe<PlayerKillEvent>(EventType::PLAYER_KILL, this, [this](const PlayerKillEvent& eventData) {
            player.GetScoreSystem().addScore(1);
          });
    }

public:
    Game() : window(sf::VideoMode(Settings::Window::Width, Settings::Window::Height), SettingsManager::getInstance().getWindowSettings().title), player(std::make_unique<DefaultMovement>(SettingsManager::getInstance().getGameSettings().defaultSpeed)) {}
    ~Game() = default;

	void start() {
		resetGame();
		sf::Clock clock;

        while (window.isOpen()) {
            sf::Time deltaTime = clock.restart();
            handleEvents();
            if (state == GameState::RUNNING) {
                update(deltaTime.asSeconds());
            }
            render();
        }

	}

    void update(float deltaTime) {
        currentLevel.update(deltaTime);
        if (currentLevel.getGameOverTriggered()) {
            state = GameState::GAME_OVER;
		}
        else if (currentLevel.getGameWonTriggered()) {
			state = GameState::GAME_WON;
        }
    }

    void render() {
        window.clear(sf::Color::Black);

        if (state == GameState::RUNNING) {
            currentLevel.render(window);
            TextDrawer::drawText(window, sf::Vector2f(2, 0), "Score: " + std::to_string(score), "minecraft.otf", sf::Color::Green);
        } else if (state == GameState::GAME_OVER) {
            renderGameOverScreen();
        } else if (state == GameState::GAME_WON) {
			renderGameWonScreen();
		}

        window.display();
    }

};
