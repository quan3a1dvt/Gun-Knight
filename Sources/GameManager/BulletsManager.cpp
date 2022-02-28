#include "BulletsManager.h"

BulletsManager::BulletsManager()
{
	m_Bullets = new vector<Bullet*>;
	GConnect->setBullets(m_Bullets);
	FOR(i, 1, BulletsNumber) {
		m_Bullets->push_back(new Bullet);
	}
	FOR(i, 1, 100) {
		m_Shoots.push_back(new Shoot);
	}
}

BulletsManager::~BulletsManager()
{
}

void BulletsManager::Init()
{
	for(Bullet* i:*m_Bullets) {
		i->Init();
	}
}

void BulletsManager::Update(float deltaTime)
{
	for (Bullet* i : *m_Bullets) i->Update(deltaTime);
}

void BulletsManager::Render(sf::RenderWindow* window)
{
	int x = 0;
	for (Bullet* i : *m_Bullets) {
		if (i->getActive()) {
			i->Render(window);
			x++;
		}
		
	}
}

void BulletsManager::Create(ShootType type, BulletType btype, string tex, sf::Vector2f pos, sf::Vector2f size, bool fromPlayer, int damage, vector<float> data)
{
	for(Shoot* i:m_Shoots) {
		if (i->getActive() == false) {
			i->Create(type, btype, tex, pos, size, fromPlayer, damage, data);
			break;
		}
	}
}

