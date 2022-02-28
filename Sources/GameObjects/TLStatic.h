#pragma once
#include "Tiled.h"
class TLStatic :public Tiled {
public:
	void Init(string name, sf::Vector2i hitboxSize);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	HitBox* GetHitBox() = 0;
private:
	sf::Sprite* m_spire;
};