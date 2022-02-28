#pragma once
#include "../GameManager/ResourceManager.h"

class Coin {
public:
	Coin();
	~Coin();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Reset(sf::Vector2f pos, int value);
	HitBox* getHitBox();
	int getValue();
	bool getActive();
	void setActive(bool active);
protected:
	Animation* m_Coin;
	HitBox* m_HitBox;
	int m_Value;
	bool m_Active;

};