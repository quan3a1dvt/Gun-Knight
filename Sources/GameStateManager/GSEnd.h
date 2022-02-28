#pragma once
#include "GameStateBase.h"
class GSEnd : public GameStateBase {
public:
	GSEnd();
	virtual ~GSEnd();

	void Exit();
	void Pause();
	void Resume();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
};