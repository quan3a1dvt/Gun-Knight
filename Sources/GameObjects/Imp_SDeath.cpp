#include "Imp_SDeath.h"
#include "../GameManager/CoinsManager.h"
#include "../GameManager/ExpsManager.h"
Imp_SDeath::Imp_SDeath(IMob* mob)
{
	m_mob = mob;
}

void Imp_SDeath::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Mob/Imp/Imp_Death_Sprite_Sheet"), sf::Vector2i(6, 1), 0.1f);
	m_animation->setScale(m_mob->getScale());
	m_animation->setOrigin(m_animation->getOrigin().x, m_animation->getOrigin().y + m_animation->GetRectSize().y * m_mob->getScale().y / 12);
}

void Imp_SDeath::Update(float deltaTime)
{
	if (m_animation->Play(deltaTime)) {
		if (Collision::BoundingBoxTest(m_mob->getHitBox(), GConnect->getPlayer()->getHitBox())) {
			GConnect->getPlayer()->LoseHp(20);
		}
		m_mob->ChangeNextState(IMState::STATE_ATTACK);
	}

	m_animation->setPosition(m_mob->getHitBox()->getPosition());
	if (m_mob->getCW()) {
		m_animation->setScale(fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
	else {
		m_animation->setScale(-fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
}

void Imp_SDeath::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}

Animation* Imp_SDeath::getSprite()
{
	return m_animation;
}
