#pragma once
#include <SFML/Graphics.hpp>
#include "GameManager/ResourceManager.h"
#include "GameStateManager/GameStateMachine.h"
#include "GameConfig.h"

class Game
{
public:
	void Run();
	~Game();
private:
	sf::RenderWindow* m_window;
	void Init();
	void Update(float deltaTime);
	void Render();
};

