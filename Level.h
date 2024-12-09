#pragma once

#include <vector>
#include <memory>
#include "GameObject.h"
#include "Wall.h"
#include "Player.h"
#include "Enemy.h"
#include "BasicAIMovement.h"
#include "CollisionChecker.h"
#include "RoomBuilder.h"
#include "RoomConfig.h"
#include "EventSystem.h"
#include "ProjectileEvent.h"
#include "DefaultMovement.h"

class Level {

private:
	Player* player = nullptr;
	bool gameOverTriggered = false;
	bool gameWonTriggered = false;

	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Wall>> walls;
	std::vector<std::unique_ptr<Projectile>> projectiles;

	SettingsManager settingsManager = SettingsManager::getInstance();
    
    Enemy* addEnemy(std::unique_ptr<Enemy> enemy) {
        enemies.push_back(std::move(enemy));
        return enemies.back().get();
    }

    void subscribeToEvents() {
        EventSystem::getInstance()->subscribe<ProjectileEvent>
        (
            EventType::SPAWN_PROJECTILE, this, [this](const ProjectileEvent& eventData) {
				spawnProjectile(eventData);
            }
        );
    }

	void unsubscribeFromEvents() {
		EventSystem::getInstance()->unsubscribeOwner(this);
	}

    void spawnProjectile(const ProjectileEvent& eventData) {
		auto projectile = createProjectile(eventData);
		projectiles.push_back(std::move(projectile));
	}

	std::unique_ptr<Projectile> createProjectile(const ProjectileEvent& eventData) {
		auto movement = std::make_unique<DefaultMovement>(settingsManager.getGameSettings().defaultSpeed);
		movement->setMovingState(eventData.dir, true);
		auto projectile = std::make_unique<Projectile>(std::move(movement));
		projectile->setPosition(eventData.GameObject->getPosition().x, eventData.GameObject->getPosition().y);
		return projectile;
	}

    void handlePlayerCollisions(Position& originalPosition) {
        if (CollisionChecker::checkLevelBounds(*player, sf::Vector2f(settingsManager.getWindowSettings().width, settingsManager.getWindowSettings().height))) {
            player->setPosition(originalPosition.x, originalPosition.y);
        }

        for (const auto& wall : walls) {
            if (CollisionChecker::checkCollision(*player, *wall)) {
                player->setPosition(originalPosition.x, originalPosition.y);
                gameOverTriggered = true;
                return;
            }
        }
    }

    void handleEnemyCollisions(Enemy& enemy, Position& originalPosition) {
        if (CollisionChecker::checkLevelBounds(enemy, sf::Vector2f(settingsManager.getWindowSettings().width, settingsManager.getWindowSettings().height))) {
            enemy.setPosition(originalPosition.x, originalPosition.y);
        }

        for (const auto& wall : walls) {
            if (CollisionChecker::checkCollision(enemy, *wall)) {
                enemy.setPosition(originalPosition.x, originalPosition.y);
            }
        }
    }

    void checkProjectileCollisions() {
		for (auto projIt = projectiles.begin(); projIt != projectiles.end();) {
			Position originalProjectilePosition = (*projIt)->getPosition();
			bool shouldEraseProjectile = false;

			for (auto& wall : walls) {
				if (CollisionChecker::checkCollision(**projIt, *wall)) {
					shouldEraseProjectile = true;
					break;
				}
			}

			for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
				if (CollisionChecker::checkCollision(**projIt, **enemyIt)) {
					shouldEraseProjectile = true;

					enemyIt = enemies.erase(enemyIt);
					break;
				} else {
					++enemyIt;
				}
			}

			if (shouldEraseProjectile) {
				projIt = projectiles.erase(projIt);
			} else {
				++projIt;
			}
		}
    }


public:
    Level() {
        subscribeToEvents();
    }
    ~Level() {
        unsubscribeFromEvents();
    }
    Level& operator=(Level&&) noexcept = default;

    void loadLevel(const RoomConfig& config) {
        gameOverTriggered = false;

        if (player) {
            player->setPosition(config.playerStartPosition.x, config.playerStartPosition.y);
        }

        RoomBuilder roomBuilder;
        walls = std::move(roomBuilder.generateWalls(config.wallSpecs));

        for (const auto& pos : config.enemyPositions) {
            addEnemy(std::make_unique<Enemy>(std::make_unique<BasicAIMovement>(settingsManager.getGameSettings().defaultSpeed)))->setPosition(pos.x, pos.y);
        }
    }

	void setPlayer(Player* player) {
		this->player = player;
	}

	std::vector<std::unique_ptr<Enemy>>& getEnemies() {
		return enemies;
	}

	bool getGameOverTriggered() const {
        return gameOverTriggered;
    }

	bool getGameWonTriggered() const {
		return gameWonTriggered;
	}

	    void update(float deltaTime) {
        if (!player) return;

        Position originalPlayerPosition = player->getPosition();
        player->update(deltaTime);
        handlePlayerCollisions(originalPlayerPosition);

        if (gameOverTriggered) return;

        for (const auto& enemy : enemies) {
            Position originalEnemyPosition = enemy->getPosition();
            enemy->update(deltaTime);
            handleEnemyCollisions(*enemy, originalEnemyPosition);

            if (CollisionChecker::checkCollision(*player, *enemy)) {
                gameOverTriggered = true;
                return;
            }
        }

        for (auto& projectile : projectiles) {
            projectile->update(deltaTime);
        }

        checkProjectileCollisions();

        if (enemies.empty()) {
            gameWonTriggered = true;
        }
    }

	void render(sf::RenderWindow& window) {
		if (player) {
			player->render(window);
		}

		for (auto& enemy : enemies) {
			enemy->render(window);
		}

		for (auto& wall : walls) {
			wall->render(window);
		}

		for (auto& projectile : projectiles) {
			projectile->render(window);
		}
	}

};
