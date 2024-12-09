#pragma once
#include "GameObject.h"
#include "Projectile.h"

struct ProjectileEvent {
	GameObject* GameObject;
	Position::Direction dir;
};
