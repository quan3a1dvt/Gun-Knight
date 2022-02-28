#include "ExpsManager.h"
ExpsManager::ExpsManager()
{
	m_Exps = new vector<Exp*>;
	GConnect->setExps(m_Exps);
	FOR(i, 0, 100) {
		m_Exps->push_back(new Exp);
	}
}

ExpsManager::~ExpsManager()
{
}

void ExpsManager::Init()
{
	FOR(i, 0, m_Exps->size() - 1) {
		m_Exps->at(i)->Init();
	}
}

void ExpsManager::Update(float deltaTime)
{
	FOR(i, 0, m_Exps->size() - 1) {
		m_Exps->at(i)->Update(deltaTime);
	}
	
}

void ExpsManager::Render(sf::RenderWindow* window)
{
	FOR(i, 0, m_Exps->size() - 1) {
		m_Exps->at(i)->Render(window);
	}
}

void ExpsManager::Create(int count, int value, sf::Vector2f pos)
{
	FOR(i, 0, m_Exps->size() - 1) {
		if (m_Exps->at(i)->getActive() == false) {
			sf::Vector2f Pos(pos.x + random::random(-15.f, 15.f), pos.y + random::random(-15.f, 15.f));
			m_Exps->at(i)->Reset(Pos, value);
			count--;
			if (count <= 0) break;
		}
	}
}
