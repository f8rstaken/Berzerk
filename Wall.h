#pragma once

#include "GameObject.h"
#include "Settings.h"
#include "Renderer.h"
#include "SettingsManager.h"

class Wall : public GameObject {

public:
	Wall() : GameObject(SettingsManager::getInstance().getTextureSettings().wall) {}
	~Wall() = default;
};
