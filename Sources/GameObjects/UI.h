#pragma once
#include "../GameManager/Singleton.h"
#include "../GameManager/ResourceManager.h"
#include "IPlayer.h"
#include "WPGun.h"
#define GUI UI::GetInstance()
class UI :public CSingleton<UI>{
public:
	UI();
	~UI();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
protected:
	sf::Vector2i m_pHp;
	sf::Vector2i m_pArmor;
	int m_pCoin;

	sf::Vector2f m_HudScale;
	sf::Vector2f m_HudPos;
	sf::Sprite m_Hud;
	sf::Sprite m_HpBar;
	vector<sf::RectangleShape> m_HpCount;

	sf::Sprite m_ArmorBar;
	vector<sf::RectangleShape> m_ArmorCount;

	sf::Sprite m_ExpBar;
	sf::Text m_ExpText;

	sf::CircleShape m_PHud;

	Animation m_CoinHud;
	sf::Text m_CoinText;

	sf::Vector2f m_ClipScale;
	sf::Vector2f m_ClipSize;
	sf::Vector2f m_ClipPos;
	AmmoType m_AmmoType;
	sf::Vector2i m_Clip;
	vector<sf::Sprite> m_Clips;
	sf::Sprite m_ClipBar;
	sf::Vector2f m_ClipBarSize;
	string cliptext;

	sf::Text m_Ammo;
	sf::RectangleShape m_GunFrame;
	
};