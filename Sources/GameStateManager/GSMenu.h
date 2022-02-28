#pragma once
#include "GameStateBase.h"
class GSMenu : public GameStateBase {
public:
	GSMenu();
	virtual ~GSMenu();

	void Exit();
	void Pause();
	void Resume();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
private:
	list<GameButton*> m_listButton;
	sf::Sprite m_background;
	sf::Text m_title;
};