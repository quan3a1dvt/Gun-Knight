#pragma once
#include "Singleton.h"
#include "ResourceManager.h"
#include "../GameObjects/Cobra.h"
#include "../GameObjects/Mage.h"
#include "../GameObjects/Imp.h"
#define MManager MobsManager::GetInstance()

class MobsManager :public CSingleton<MobsManager> {
public:
	MobsManager();
	~MobsManager();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Spawn(int mobtype, int number);
protected:
	std::vector<IMob*>* m_Mobs;
};