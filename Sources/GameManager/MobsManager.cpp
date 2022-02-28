#include "MobsManager.h"
#include <typeinfo>
MobsManager::MobsManager()
{
	m_Mobs = new vector<IMob*>;
	GConnect->setMobs(m_Mobs);
	FOR(i, 1, eachmtypenumber) m_Mobs->push_back(new Cobra);
	FOR(i, 1, eachmtypenumber) m_Mobs->push_back(new Mage);
	FOR(i, 1, eachmtypenumber) m_Mobs->push_back(new Imp);
	//FOR(i, 0, m_Mobs->size() - 1) cout << typeid(m_Mobs->at(i)).name() << endl;
}

MobsManager::~MobsManager()
{
}

void MobsManager::Init()
{
	FOR(i, 0, m_Mobs->size() - 1) {
		m_Mobs->at(i)->Init();
	}
}

void MobsManager::Update(float deltaTime)
{
	FOR(i, 0, m_Mobs->size() - 1) {
		if (m_Mobs->at(i)->getActive()) {
			
			m_Mobs->at(i)->Update(deltaTime);
		}
	}
}
bool cmp(IMob* a, IMob* b) {
	float ya = a->getHitBox()->getPosition().y - a->getHitBox()->getOrigin().y + a->getHitBox()->getSize().y * a->getHitBox()->getScale().y;
	float yb = b->getHitBox()->getPosition().y - b->getHitBox()->getOrigin().y + b->getHitBox()->getSize().y * b->getHitBox()->getScale().y;

	if (ya < yb) return true;
	else return false;
}
vector<IMob*> m_mobs;
void MobsManager::Render(sf::RenderWindow* window)
{
	/*FOR(i, 0, m_Mobs->size() - 1) {
		if (m_Mobs->at(i)->getActive()) {
			m_Mobs->at(i)->Render(window);
		}
	}*/
	m_mobs.clear();
	FOR(i, 0, GConnect->getMobs()->size() - 1) {
		if (GConnect->getMobs()->at(i)->getActive()) m_mobs.push_back(GConnect->getMobs()->at(i));
	}
	bool check = false;
	sort(m_mobs.begin(), m_mobs.end(), cmp);
	if (m_mobs.empty() == false) {
		FOR(i, 0, m_mobs.size() - 1) {
			float ya = m_mobs[i]->getHitBox()->getPosition().y - m_mobs[i]->getHitBox()->getOrigin().y + m_mobs[i]->getHitBox()->getSize().y * m_mobs[i]->getHitBox()->getScale().y;
			float yb = GConnect->getPlayer()->getHitBox()->getPosition().y - GConnect->getPlayer()->getHitBox()->getOrigin().y + GConnect->getPlayer()->getHitBox()->getSize().y * GConnect->getPlayer()->getHitBox()->getScale().y;
			if (ya >= yb && check == false) {
				GConnect->getPlayer()->Render(window);
				check = true;
			}
			m_mobs[i]->Render(window);
		}
		if (check == false) GConnect->getPlayer()->Render(window);
	}
	else GConnect->getPlayer()->Render(window);

}

void MobsManager::Spawn(int mobid, int number)
{
	//printf("%d %d\n", mobid, number);
	FOR(num, 1, number) {
		FOR(i, (mobid - 1) * eachmtypenumber, mobid * eachmtypenumber - 1) {
			if (m_Mobs->at(i)->getActive() == false) {
				//printf("%d\n", i);
				m_Mobs->at(i)->Spawn();
				break;
			}
		}
	}
}



