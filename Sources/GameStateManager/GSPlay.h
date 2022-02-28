#pragma once
#include "GameStateBase.h"

class GSPlay : public GameStateBase {
public:
	GSPlay();
	virtual ~GSPlay();

	void Exit();
	void Pause();
	void Resume();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
private:
	Player* m_Player;
	sf::Sprite m_Cursor;
	sf::View* m_pView;
	bool m_Active;

	float m_waitPause;
	float m_currentPauseTime;
	bool m_canPause;

	sf::Sprite m_PauseFrame;
	vector<sf::Sprite*> m_PauseTitle;
	list<GameButton*> m_listButton;

	sf::Text m_Res;
};