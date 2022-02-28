#pragma once
#include "../GameManager/ResourceManager.h"


class Weapon {
public:
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
	virtual float GetDamage() = 0;
protected:
	sf::Vector2f phitboxPos;
	sf::Vector2f phitboxScale;
	sf::Vector2f phitboxSize;
	sf::Vector2f mousePos;
	sf::Vector2f wpScale;
	sf::Vector2f wpPos;
	sf::Vector2u wpSize;
	
	float angle;
	bool isPlayerCW;
	bool m_isAttacking;
	float m_currentTime;
	float m_attackTime;
	float m_waitTime;
};