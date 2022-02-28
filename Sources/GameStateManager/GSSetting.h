#pragma once
#include "GameStateBase.h"
class GSSetting : public GameStateBase {
public:
	GSSetting();
	virtual ~GSSetting();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
private:
	list<GameButton*> m_listButton;
	sf::Text m_title;
	sf::Sprite m_background;
};