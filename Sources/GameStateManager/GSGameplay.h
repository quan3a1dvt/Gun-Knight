#pragma once
#include "GameStateBase.h"
class GSGameplay : public GameStateBase {
public:
	GSGameplay();
	virtual ~GSGameplay();

	void Exit();
	void Pause();
	void Resume();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};