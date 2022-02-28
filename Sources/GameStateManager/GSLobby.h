#pragma once
#include "GameStateBase.h"
#include "../GameObjects/Player.h"
#include "../GameManager/BulletsManager.h"
#include "../GameObjects/UI.h"
class GSLobby : public GameStateBase {
public:
	GSLobby();
	virtual ~GSLobby();

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

};