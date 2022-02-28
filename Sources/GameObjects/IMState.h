#pragma once
#include "../GameManager/ResourceManager.h"
#include "../GameManager/CoinsManager.h"
#include "../GameManager/ExpsManager.h"

class IMState {
public:
	enum STATE
	{
		STATE_SPAWN,
		STATE_IDLE,
		STATE_RUN,
		STATE_ATTACK,
		STATE_DEATH,
		SNULL,
	};
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
	virtual Animation* getSprite() = 0;
};