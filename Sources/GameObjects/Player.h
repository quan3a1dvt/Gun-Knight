#pragma once

#include "IPlayer.h"
#include "HitBox.h"
#include "WPSword.h"
#include "WPGun.h"



class Player : public IPlayer {
public:
	Player();
	~Player();
	void ChangeNextState(IPState::STATE nextState);
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	HitBox* getHitBox();
	void LoseHp(int hp);
	void LoseArmor(int armor);
	sf::Vector2i getHp();
	sf::Vector2i getArmor();
	sf::Vector2f getScale();
	bool getCW();
	void setCW(bool cw);
	WPSword* GetMeleeWP();
	void Move(float movex, float movey);
	void setActive(bool active);
	bool getActive();
	WPGun* getCurrentWP();
	int getCoin();
	void addCoin(int coin);
	sf::Vector2i getExp();
	void addExp(int exp);
	void setExp(int exp);
	int getLevel();
	bool getHurt();
private:
	void PerformStateChange();
	HitBox* m_HitBox;
	
	sf::Vector2f m_Scale;

	IPState::STATE m_nextState;
	IPState* m_currentState;
	IPState* m_runState;
	IPState* m_deathState;
	IPState* m_attackState;
	IPState* m_idleState;

	vector<WPGun*> m_wpGuns;

	int m_currentGunSlot;
	int m_currentGunSlotCount;
	int m_maxGunSlotCount;
	float m_currentTime;
	float m_waitTime;
	WPSword* m_wpSword;
	vector<vector<Tile*>>* m_Tiles;
	vector<vector<TileBox*>>* m_TileBoxes;

	sf::Vector2i* m_RoomPos;
	bool m_cw;

	bool m_Active;
	int m_Coin;
	

	bool m_Hurt;
	float m_waitHurt;
	float m_currentHurtTime;

	bool m_ShowHurt;
	float m_waitShowHurt;
	float m_currentShowHurtTime;


	sf::Vector2i m_Hp;
	sf::Vector2i m_Armor;
	sf::Vector2i m_Exp;
	int m_Level;
	

	
};