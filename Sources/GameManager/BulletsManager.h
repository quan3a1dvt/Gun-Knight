#pragma once
#include "Singleton.h"
#include "ResourceManager.h"
#include "../GameObjects/Shoot.h"
#define BManager BulletsManager::GetInstance()
class BulletsManager :public CSingleton<BulletsManager> {
public:
	BulletsManager();
	~BulletsManager();
	void Init();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void Create(ShootType type, BulletType btype, string tex, sf::Vector2f pos, sf::Vector2f size, bool fromPlayer, int damage, vector<float> data);
	
protected:
	std::vector<Bullet*>* m_Bullets;
	std::vector<Shoot*> m_Shoots;
};