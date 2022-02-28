#pragma once

#include "../GameObjects/Exp.h"
#include "Singleton.h"
#define EManager ExpsManager::GetInstance()

class ExpsManager :public CSingleton<ExpsManager> {
public:
	ExpsManager();
	~ExpsManager();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Create(int count, int value, sf::Vector2f pos);
protected:
	vector<Exp*>* m_Exps;
};