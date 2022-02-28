#pragma once
#include "../GameManager/ResourceManager.h"
#include "HitBox.h"
class Tiled {
public:
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
	virtual HitBox* GetHitBox() = 0;
protected:
	HitBox* m_hitbox;
};