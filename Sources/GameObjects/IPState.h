#pragma once
#include "../GameManager/ResourceManager.h"


class IPState {
public:
	enum STATE
	{
		STATE_RUN,
		STATE_IDLE,
		STATE_DEATH,
		STATE_ATTACK,
		SNULL,
	};
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;

};