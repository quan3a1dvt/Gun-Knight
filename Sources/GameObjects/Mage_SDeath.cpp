#include "Mage_SDeath.h"

Mage_SDeath::Mage_SDeath(IMob* mob)
{
	m_mob = mob;
}

void Mage_SDeath::Init()
{
	m_animation = new Animation(*ASSET->getTexture("Mob/Mage/Mage_Death_Sprite_Sheet"), sf::Vector2i(8, 1), 0.1f);
	m_animation->setScale(m_mob->getScale());
	m_animation->setOrigin(m_animation->getOrigin().x - m_animation->GetRectSize().x * m_mob->getScale().x / 14, m_animation->getOrigin().y);
}

void Mage_SDeath::Update(float deltaTime)
{
	if (m_animation->Play(deltaTime)) {
		m_mob->setActive(false);
		GConnect->MobDeath(2);
		CManager->Create(2, 1, m_mob->getHitBox()->getPosition());
		EManager->Create(2, 1, m_mob->getHitBox()->getPosition());
	}

	m_animation->setPosition(m_mob->getHitBox()->getPosition());
	if (m_mob->getCW()) {
		m_animation->setScale(fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
	else {
		m_animation->setScale(-fabs(m_animation->getScale().x), fabs(m_animation->getScale().y));
	}
}

void Mage_SDeath::Render(sf::RenderWindow* window)
{
	window->draw(*m_animation);
}

Animation* Mage_SDeath::getSprite()
{
	return m_animation;
}
