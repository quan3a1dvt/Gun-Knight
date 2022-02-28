#pragma once
#include "../GameManager/ResourceManager.h"
enum ShopItemType {
	DEFAULT = 0,
	PISTOL_B,
	SHOTGUN_B,
	SMG_B,
	BANDAGE,
};
class ShopItem {
public:
	ShopItem();
	~ShopItem();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Create(sf::Vector2f pos, ShopItemType type);
	
	
protected:
	sf::Vector2f m_Scale;
	sf::Sprite m_Item;
	sf::Text m_PriceText;
	int m_Price;
	HitBox m_HitBox;
	ShopItemType m_Type;
	float m_currentTime;
	float m_waitTime;
};