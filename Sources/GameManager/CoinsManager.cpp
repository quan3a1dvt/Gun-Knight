#include "CoinsManager.h"
CoinsManager::CoinsManager()
{
	m_Coins = new vector<Coin*>;
	GConnect->setCoins(m_Coins);
	FOR(i, 0, 100) {
		m_Coins->push_back(new Coin);
	}
}

CoinsManager::~CoinsManager()
{
}

void CoinsManager::Init()
{
	FOR(i, 0, m_Coins->size() - 1) {
		m_Coins->at(i)->Init();
	}
}

void CoinsManager::Update(float deltaTime)
{
	FOR(i, 0, m_Coins->size() - 1) {
		m_Coins->at(i)->Update(deltaTime);
	}
}

void CoinsManager::Render(sf::RenderWindow* window)
{
	FOR(i, 0, m_Coins->size() - 1) {
		m_Coins->at(i)->Render(window);
	}
}

void CoinsManager::Create(int count, int value, sf::Vector2f pos)
{
	FOR(i, 0, m_Coins->size() - 1) {
		if (m_Coins->at(i)->getActive() == false) {
			sf::Vector2f Pos(pos.x + random::random(-15.f, 15.f), pos.y + random::random(-15.f, 15.f));
			m_Coins->at(i)->Reset(Pos, value);
			count--;
			if (count <= 0) break;
		}
	}
}
