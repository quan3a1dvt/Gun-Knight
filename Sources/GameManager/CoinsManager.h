#pragma once

#include "../GameObjects/Coin.h"
#include "Singleton.h"
#define CManager CoinsManager::GetInstance()

class CoinsManager :public CSingleton<CoinsManager> {
public:
	CoinsManager();
	~CoinsManager();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Create(int count, int value, sf::Vector2f pos);
protected:
	vector<Coin*>* m_Coins;
};