#pragma once
#include "GameStateBase.h"
class GSPause : public GameStateBase {
public:
	GSPause();
	virtual ~GSPause();

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

	float m_waitPause;
	float m_currentPauseTime;
	bool m_canPause;
};